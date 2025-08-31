# massif2img

`massif2img` is a program that helps with generating visualizations from [valgrind massif](https://valgrind.org/docs/manual/ms-manual.html) output files.

## Why?

I needed graphs from a heap profiling for an academic paper and the collection of programs to generate such looked sparse.

The built-in method is `ms_print`, but it generates ASCII visualizations, which is not feasible for presentation.

There is [massif-visualizer](https://github.com/KDE/massif-visualizer) by KDE, but it is more made to be interactive.
I needed to generate graphics automatically and not go into a graphical program, wait for it to load up and press `Save to Image` for each output file I had.

## What can it do?

`massif2img` generally generates two files:
* a csv file
* a python script to generate simple graphics from the csv file

The csv file should be enough to generate graphics on your own, but for quick graphics, that do not require custom formatting, the python script provides a convenient solution.

## Why does it not generate images directly?

It is meant to be used to extract data from the massif output to generate visualizations on demand, such as in an automated `make` process.

>I don't want to push images to my git repo!

The workflow would be:

* run `valgrind`, get `massif.out`
* `massif2img massif.out` generates `massif.out.csv`, which itself would already be sufficient and `massif.out.py`
	* massif.out.py` produces `massif.out.pdf`
* copy `massif.out.csv` and `massif.out.py` where you store your images
* e.g. in your Makefile add something like
```Makefile
massif.out.pdf: massif.out.csv
	python3 massif.out.py
```

For me, this workflow is perfect.
If you find it too cumbersome, you can either leave a suggestion on how to improve this or this program might not be for you, sorry :(.