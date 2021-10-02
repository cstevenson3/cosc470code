''' For a given reconstruction binary, call it with combinations of sample size, model etc. '''

import itertools
from time import sleep
import subprocess
import os
import shutil
import json

import pymeshlab

def filename_of_combo(label, name, samples):
    return label + "-" + name + "-" + str(samples) + ".ply"

def filepath_of_combo(config, name, samples):
    return config["automation_folder"] + filename_of_combo(config["label"], name, samples)

def call_reconstruct(config, filename):
    input_text = "test" + "\n" + filename + "\n"
    p = subprocess.run(config["binary"], input=input_text, text=True)

def reconstruct_combos(config, combos):
    for combo in combos:
        model_name = combo[0]
        plane_sample = combo[1]

        original = config["test_model_originals_folder"] + model_name + ".ply"
        sample = config["test_model_samples_folder"] + config["sample_prefix"] + str(plane_sample) + "/" + model_name + ".txt"
        
        call_reconstruct(config, sample)

        # copy output over
        sleep(0.3)
        output_file = config["output_file"]
        dest = filepath_of_combo(config, model_name, plane_sample)
        if os.path.exists(dest):
            os.remove(dest)
        shutil.copy(output_file, dest)
        sleep(0.1)

def hausdorff_stats(model1, model2):
    ms = pymeshlab.MeshSet()
    ms.load_new_mesh(os.path.abspath(model1))  # from
    ms.load_new_mesh(os.path.abspath(model2))  # to
    return ms.hausdorff_distance(sampledmesh=0, targetmesh=1)

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
    simple10 = query_stats(stats, model="simple-branch", plane_samples=10)
    simple10rm = pull_values(simple10, ["label", "hd_default_forward.mean"])
    print(simple10rm)

def main():
    fp = open("Modifications/analysis/config.json")
    config = json.load(fp)

    # generate combinations
    model_names = config["test_model_names"]
    plane_samples = config["plane_samples"]
    combos = list(itertools.product(model_names, plane_samples))

    if config["reconstruct"]:
        reconstruct_combos(config, combos)

    if config["analyse"]:
        analyse(config, combos)

    if config["show_stats"]:
        show_stats(config)

if __name__ == "__main__":
    main()