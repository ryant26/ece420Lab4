import common

def print_problem_header(problem_size):
	print("==========================================")
	print("Problem Size:", problem_size)
	print("==========================================")

def perform_run(problem_Size):
	print_problem_header(problem_Size)
	common.run_datagen(problem_Size)
	all_correct = True

	for i in range(1,problem_Size+1):
		if (problem_Size % i == 0):
			common.run_main(problem_Size)
			if (common.is_result_correct()):
				out = "Correct"
			else:
				out = "Wrong!!!"
				all_correct = False

			print("Threads", i, ":", out)

	if (all_correct):
		print("TEST WAS SUCCESSFUL!")
	else:
		print("TEST FAILED!!")

	return all_correct;

def perform_multiple_sizes(sizes):
	result = True;
	for i in sizes:
		result = result and perform_run(i)

	print("=====================================================================")

	if (result):
		print("All problem sizes passed")
	else:
		print("There were failures!!!!")

perform_multiple_sizes([3, 5, 10, 15, 20, 30, 40, 50, 100, 100, 100, 200, 300])
common.cleanup()