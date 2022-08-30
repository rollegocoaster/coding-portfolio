import numpy as np
import math
import scipy.stats as stats
import matplotlib.pyplot as plt
import pandas as pd

def generateRandomColors(numcolors, displayColor = False):
    """
    helper function that generates numcolors random color and displays them to the user
    """
    color = []
    x = []
    for i in range(numcolors):
        color += [(np.random.choice(range(0,255),size=3)/255)]
        x += [i]
    if displayColor:
        #displays colors
        testcolor, testcolorax = plt.subplots(figsize=(numcolors,1))
        testcolorax.bar(x,height=1,width=1,color=color)
        testcolorax.set_axis_off()
        plural = numcolors>1
        if numcolors < 10:
            numcolors = 10
        testcolorax.set_title("generated color"+ ("s" if plural else "") ,fontsize=numcolors)
    return color

# create a list of cards
suits = ["♦","♣","♠","♥"]
faces = ["A"]+[str(i+1) for i in range(1,10)] + ["J","Q","K"]
cards = []
for f in faces:
    for s in suits:
        cards += [f+" "+s]
cards += ["jo","jo "]
print(cards)

def cardSim(cards=cards):
    """
    simulate how many draws it would take to take to draw four of the following five cards: 
    3 of hearts, the Jack of diamonds, the 4 of clubs, and both of the jokers
    """
    # a series whose indices are the shuffled cards
    # and data equaling the number of draws it would take to draw that card
    shuffled = pd.Series(data = range(1,55), index=np.random.choice(cards,54,replace=False))
    
    #the three of hearts, the jack of diamonds, the four of clubs, and both of the jokers.
    significantCards = ["3 ♥","J ♦","4 ♠","jo","jo "]
    
    #locate all of the significant cards
    sigCardLocations = shuffled.loc[significantCards]
    # return the second largest number in the list 
    # which would be the 4th card you'd encounter if you continuously drew from the top
    return sigCardLocations.nlargest(2)[1]


# simulate 25,000 times
simulations = []
for i in range(25000):
    simulations += [cardSim()]



simSeries = pd.Series(simulations)

fig, ax = plt.subplots(figsize=[16,8])
density = True # set this to false if you want the histogram to be a frequency histogram
color = generateRandomColors(1)
ax.hist(simulations,bins=range(0,55),color=color, alpha=.5,edgeColor="white",density=density)

#Compute the mean, median, and mode for this dataset, 
s = simSeries.agg(['mean','median'])
smode = simSeries.mode()[0]

#indicate them on the plot using a line, with linstyles of green dashed, red dotted, and black solid, respectively.
ax.axvline(s["mean"],linestyle="--",linewidth=3,color="g",label="mean:"+str(s["mean"]))
ax.axvline(s["median"],linestyle=":",linewidth=3,color="r",label="median:"+str(s["median"]))
ax.axvline(smode,linestyle="-",linewidth=3,color="k",label="mode:"+str(smode))
ax.set_xticks(range(0,56,5))
ax.set_ylabel("Density" if density else "Frequency",fontsize=16)
ax.set_xlabel("Number of draws",fontsize=16)
ax.set_title("Histogram of simulated number of Draws",fontsize=24)
legend = plt.figlegend()