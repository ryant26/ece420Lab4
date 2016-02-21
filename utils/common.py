from subprocess import call
from subprocess import check_output

def run_datagen(problem_size):
	call(["../bin/datagen", "-s", str(problem_size)])

def run_main(threads):
	call(["../bin/main", str(threads)])

def run_serialtester():
	call(["../bin/serialtester"])

def cleanup():
	call("rm -rf *.txt", shell=True)
	call(["rm", "-f", "data_input"])
	call(["rm", "-f", "data_output"])
	
def is_result_correct():
	result = check_output("../bin/serialtester")
	if "Congratulation" in result.decode("utf-8"):
		return True
	else:
		return False

def get_runtime():
	with open('data_output', 'rb') as f:
		for i, line in enumerate(f):
			if i == 2:
				return float(line.strip())
