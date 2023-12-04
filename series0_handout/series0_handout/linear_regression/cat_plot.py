"""
Plots the linear regression and adds pretty cats to it all
"""

from matplotlib import pyplot as plt
import numpy 
import matplotlib
plt.xkcd()
Y=[ 6.5 , 7.2 , 7.3 , 7.6 , 7.7 , 7.9 , 7.9 , 7.9 , 7.9 , 8.0 , 8.3, 8.5 , 8.6 , 8.8 , 8.8]

X =[2 , 2.2 , 2.4 , 2.2 , 2.6 , 2.2 , 2.4 , 2.4 , 2.5 , 2.7 , 2.6 , 2.2 , 2.5 , 2.5 , 2.5 ]

try:
    plt.scatter(X, Y, 900*numpy.ones_like(X),c="g", alpha=0.5, marker=u'$\U0001F431$', label="Observed data")
except Exception:
    # CPP'21: some people have problems with the cat plot but I can't test it at the moment.
    # Removing the unicode marker appears to fix it.
    # TODO: refine this to catch the correct exception only
    plt.scatter(X, Y, 900*numpy.ones_like(X),c="g", alpha=0.5, label="Observed data")


x = numpy.linspace(min(X), max(X),100)
regression = numpy.loadtxt("coeffs_regression.txt")
plt.plot(x, regression[1]*x+regression[0], '--', label="Regression")
plt.xlabel("Body weight (kg)")
plt.ylabel("Mass of heart (g)")

plt.legend(loc=0)
plt.show()


  
