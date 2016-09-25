import maxflow
import numpy as np

def readdata(f1):
	preferenceMatrix = []
	with open(f1) as f:
		for eachLine in f:
			preferenceMatrix.append([int(pref) for pref in eachLine.split(",")])
	return np.array(preferenceMatrix)

#(a)
def maxTasks(matrix):
	print ""
	print "Part (a):"
    #print matrix
	g = maxflow.Graph[int](1,1)
	numberOfEmployees = matrix.shape[0]
	numberOfTasks = matrix.shape[1]
	print "Total number of tasks:", numberOfTasks
	empnodes = g.add_nodes(numberOfEmployees)
	jobnodes = g.add_nodes(numberOfTasks)
	
	for i in xrange(numberOfEmployees):
		g.add_tedge(empnodes[i], numberOfTasks, 0)
	for i in xrange(numberOfTasks):
		g.add_tedge(jobnodes[i], 0, 1)

	for i in xrange(numberOfEmployees):
		for j in xrange(numberOfTasks):
			if matrix[i][j] == 1 or matrix[i][j] == 2:
				g.add_edge(empnodes[i], jobnodes[j], 1, 0)

	bestCase = g.maxflow()
	print "Maximum no of tasks that can be assigned:", bestCase
	print "" 
matrix = readdata("preferenceMatrix.txt")
maxTasks(matrix)



#(b)
from pulp import *
for i in xrange(matrix.shape[0]):
	for j in xrange(matrix.shape[1]):
		if matrix[i][j] == -1:
			matrix[i][j] = 0

print ""
print "Part (b):"
assignProblem = LpProblem("Best Assignment", LpMinimize)
variables = [LpVariable("v"+str(i)+'_'+str(j), None, None, LpBinary) for i in xrange(matrix.shape[0]) for j in xrange(matrix.shape[1]) if matrix[i][j]>0]
#print variables

#objective
def fetchi(var):
	return int(var.name[1:].split("_")[0])
def fetchj(var):
	return int(var.name[1:].split("_")[1])

assignProblem += sum(matrix[fetchi(var)][fetchj(var)]*var for var in variables)

#constraints
for i in xrange(matrix.shape[0]):
    #an employee cannot be assigned more than two tasks
	assignProblem += sum(var for var in variables if fetchi(var) == i) <= 2
	#an employee must be assigned atleast one task
	assignProblem += sum(var for var in variables if fetchi(var) == i) >= 1

for j in xrange(matrix.shape[1]):
    #all tasks must be assigned to some employee
	assignProblem += sum(var for var in variables if fetchj(var) == j) == 1


#print assignProblem
assignProblem.solve()
for var in assignProblem.variables(): 
	#print var.name, "=", var.varValue 
	if var.varValue == 1:
		print "Emp:", fetchi(var), "Job:", fetchj(var), "Preference:", matrix[fetchi(var)][fetchj(var)]

#print "sumOfPreferences=", value(assignProblem.objective)
 
print "Average preference:", value(assignProblem.objective) / matrix.shape[1]
