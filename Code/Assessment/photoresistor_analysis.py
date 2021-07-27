import pandas as pd
import numpy as np
from scipy.stats import norm, shapiro, t
import matplotlib.pyplot as plt
from statistics import NormalDist

xls = pd.ExcelFile('C://DATA//Git//Flowmeter-Alert//Data//Photoresistor.xlsx')

def analyze_photo(light_level='low'):
    df = pd.read_excel(xls, 'photoresistor_'+light_level)   
    uncovered = df["Uncovered Top Resistor"]
    laserd = df["Lasered Top Resistor"]
    diff = (laserd-uncovered)
    # x_range = np.arange(np.min(diff), np.max(diff), 1)
    
    mu, std = norm.fit(diff) # mu is sample mean, std is sample dist
    
    # avg = np.mean(diff)
    # std = np.std(diff, ddof=1)
    plt.hist(diff, bins=25, density=True)
    
    xmin, xmax = np.min(diff), np.max(diff)
    x = np.linspace(xmin, xmax, 100)
    p = norm.pdf(x, mu, std)
    
    z = NormalDist().inv_cdf(0.05/100)
    lessthan05 = z * std + mu
    
    """
    NULL hypo: mean is 250
    REJECT: t0 > t_(alpha, n-1) ==> mean is larger than 200
    
    alpha = 0.00001 (99.999%)
    """
    print("t_(alpha, n-1) is: {}".format(t.ppf(1-0.00001, diff.size-1))) # this value is correct
    print("t_0 is: {}".format((mu-250)/(std/diff.size**.5))) # mu and std are both sample
    plt.plot(x, p, 'k', linewidth=2)
    plt.title("Photoresistor value difference at {} light level".format(light_level))
    plt.show()
    print(shapiro(diff))
    print("N: {}, Mean: {:.02f}, STD: {:.02f}, <0.05%: {:.02f}".format(diff.size, mu, std, lessthan05))
    print()
    
for light_level in ['low', 'medium', 'high', 'vhigh']:
    analyze_photo(light_level)