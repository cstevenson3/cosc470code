''' For a given reconstruction binary, call it with combinations of sample size, model etc. '''

import itertools
from time import sleep
import subprocess
import os
import shutil
import json

import pymeshlab

def filename(label, name, samples):
    return label + "-" + name + "-" + str(samples)

def filename_of_combo(label, name, samples):
    return filename(label, name, samples) + ".ply"

def filepath_of_combo(config, name, samples):
    return config["automation_folder"] + filename_of_combo(config["label"], name, samples)

def filepath_of_snapshot(config, name, samples):
    return config["snapshot_folder"] + filename(config["label"], name, samples) + ".png"

def call_reconstruct(config, filename):
    input_text = "test" + "\n" + filename + "\n"
    p = subprocess.run(config["binary"], input=input_text, text=True)

def reconstruct_combos(config, combos):
    for combo in combos:
        model_name = combo[0]
        plane_sample = combo[1]

        original = config["test_model_originals_folder"] + model_name + ".ply"
        # quick hack to reconstruct simple-branch.txt for the 2-6 model
        sample_name = model_name
        if sample_name == "simple-branch-2-6":
            sample_name = "simple-branch"
        sample = config["test_model_samples_folder"] + config["sample_prefix"] + str(plane_sample) + "/" + sample_name + ".txt"
        
        call_reconstruct(config, sample)

        # copy output over
        sleep(0.3)
        output_file = config["output_file"]
        dest = filepath_of_combo(config, model_name, plane_sample)
        if os.path.exists(dest):
            os.remove(dest)
        shutil.copy(output_file, dest)
        sleep(0.1)

def hausdorff_stats(model1, model2, options={}):
    ms = pymeshlab.MeshSet()
    ms.load_new_mesh(os.path.abspath(model1))  # from
    ms.load_new_mesh(os.path.abspath(model2))  # to
    stats = ms.hausdorff_distance(sampledmesh=0, targetmesh=1, **options)
    return stats

def append_hd_stats(combo_stats, label, hd_stats):
    mean = hd_stats["mean"]
    max = hd_stats["max"]
    RMS = hd_stats["RMS"]

    combo_stats[label] = {"mean": mean, "max": max, "RMS": RMS}

def analyse(config, combos):
    combo_objects = []
    if config["append_to_stats"]:
        fp = open(config["automation_folder"] + "stats.json", mode="r")
        existing_stats = json.load(fp)
        combo_objects = existing_stats

    for combo in combos:
        model_name = combo[0]
        plane_sample = combo[1]
        
        combo_object = {"label": config["label"], 
                        "model": model_name, 
                        "plane_samples": plane_sample}
        original = config["test_model_originals_folder"] + model_name + ".ply"
        output = filepath_of_combo(config, model_name, plane_sample)

        # hausdorff default
        forward_stats = hausdorff_stats(original, output)
        append_hd_stats(combo_object, "hd_default_forward", forward_stats)
        reverse_stats = hausdorff_stats(output, original)
        append_hd_stats(combo_object, "hd_default_reverse", reverse_stats)

        # hausdorff faces
        forward_stats = hausdorff_stats(original, output, options={"samplevert":False, "sampleface":True})
        append_hd_stats(combo_object, "hd_faces_forward", forward_stats)
        reverse_stats = hausdorff_stats(output, original, options={"samplevert":False, "sampleface":True})
        append_hd_stats(combo_object, "hd_faces_reverse", reverse_stats)

        combo_objects.append(combo_object)

    fp = open(config["automation_folder"] + "stats.json", mode="w")
    json.dump(combo_objects, fp)

def query_stats(stats, label=None, model=None, plane_samples=None):
    ''' filter stats '''
    result = []
    for stat in stats:
        if stat["label"] == label or label == None:
            if stat["model"] == model or model == None:
                if stat["plane_samples"] == plane_samples or plane_samples == None:
                    result.append(stat)
    return result

def pull_values(stats, values=[]):
    result = []
    for stat in stats:
        pulled = dict()
        for v in values:
            tree = v.split(".")
            obj = stat
            for token in tree:
                obj = obj[token]
            pulled[v] = obj
        result.append(pulled)
    return result

def show_stats(config):
    fp = open(config["automation_folder"] + "stats.json", mode="r")
    stats = json.load(fp)
    simple10 = query_stats(stats, model="simple-branch-2-6", plane_samples=40)
    simple10rm = pull_values(simple10, ["label", "plane_samples", "hd_faces_forward.mean"])
    print(simple10rm)

def take_snapshot(config, model_name, plane_samples):
        model_path = filepath_of_combo(config, model_name, plane_samples)
        snapshot_path = filepath_of_snapshot(config, model_name, plane_samples)
        ms = pymeshlab.MeshSet()
        ms.load_new_mesh(os.path.abspath(model_path))
        ms.snapshot(imagewidth=512, imageheight=768, imagefilename=snapshot_path)

def take_snapshots(config, combos):
    for combo in combos:
        model_name, plane_samples = combo
        take_snapshot(config, model_name, plane_samples)

def main():
    fp = open("Modifications/analysis/config.json")
    config = json.load(fp)

    # generate combinations
    model_names = config["test_model_names"]
    plane_samples = config["plane_samples"]
    combos = list(itertools.product(model_names, plane_samples))

    if config["reconstruct"]:
        reconstruct_combos(config, combos)
    
    if config["take_snapshots"]:
        take_snapshots(config, combos)

    if config["analyse"]:
        analyse(config, combos)

    if config["show_stats"]:
        show_stats(config)

if __name__ == "__main__":
    main()