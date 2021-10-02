''' For a given reconstruction binary, call it with combinations of sample size, model etc. '''

import itertools
from time import sleep
import subprocess
import os
import shutil
import json

def filename_of_combo(label, name, samples):
    return label + "-" + name + "-" + str(samples) + ".ply"

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
        labelled_file = filename_of_combo(config["label"], model_name, plane_sample)
        dest = config["automation_folder"] + labelled_file
        if os.path.exists(dest):
            os.remove(dest)
        shutil.copy(output_file, dest)
        sleep(0.1)

def analyse(config, combos):
    pass

def main():
    fp = open("Modifications/analysis/config.json")
    config = json.load(fp)

    # generate combinations
    model_names = config["test_model_names"]
    plane_samples = config["plane_samples"]
    combos = itertools.product(model_names, plane_samples)
    
    if config["reconstruct"]:
        reconstruct_combos(config, combos)

    if config["analyse"]:
        analyse(config, combos)

if __name__ == "__main__":
    main()