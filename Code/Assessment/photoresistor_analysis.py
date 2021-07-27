import pandas as pd
import numpy as np
from scipy.stats import norm, shapiro, t
import matplotlib.pyplot as plt
from statistics import NormalDist

xls = pd.ExcelFile('C://Users//USER//Desktop//BME Year 2//BME261//Project//'
                   'Flowmeter-Alert-main//Flowmeter-Alert-main//Flowmeter-Alert-main//Data//Photoresistor.xlsx')

def analyze_photo(light_level='low'):
    df = pd.read_excel(xls, 'photoresistor_'+light_level)   
    uncovered = df["Uncovered Top Resistor"]
    laserd = df["Lasered Top Resistor"]
    diff = (laserd-uncovered)
    # x_range = np.arange(np.min(diff), np.max(diff), 1)

    # scatter plot
    df4 = pd.read_excel(xls, 'photoresistor_low')
    uncovered4 = df4["Uncovered Top Resistor"]
    laserd4 = df4['Lasered Top Resistor']
    low = []

    df3 = pd.read_excel(xls, 'photoresistor_medium')
    uncovered3 = df3["Uncovered Top Resistor"]
    laserd3 = df3['Lasered Top Resistor']
    medium = []

    df2 = pd.read_excel(xls, 'photoresistor_high')
    uncovered2 = df2["Uncovered Top Resistor"]
    laserd2 = df2['Lasered Top Resistor']
    high = []

    df1 = pd.read_excel(xls, 'photoresistor_vhigh')
    uncovered1 = df1["Uncovered Top Resistor"]
    laserd1 = df1['Lasered Top Resistor']
    vhigh = []

    s4 = []
    s3 = []
    s2 = []
    s1 = []

    for i in range(len(uncovered4)):
        low.append(4)
        s4.append(5)
    for i in range(len(uncovered3)):
        medium.append(3)
        s3.append(5)
    for i in range(len(uncovered2)):
        high.append(2)
        s2.append(5)
    for i in range(len(uncovered1)):
        vhigh.append(1)
        s1.append(5)

    plt.scatter(uncovered4, low, s=s4, c='darkorange', label='Uncovered')
    plt.scatter(laserd4, low, s=s4, c='darkblue', label='lasered')
    plt.scatter(uncovered3, medium, s=s3, c='darkorange')
    plt.scatter(laserd3, medium, s=s3, c='darkblue')
    plt.scatter(uncovered2, high, s=s2, c='darkorange')
    plt.scatter(laserd2, high, s=s2, c='darkblue')
    plt.scatter(uncovered1, vhigh, s=s1, c='darkorange')
    plt.scatter(laserd1, vhigh, s=s1, c='darkblue')

    plt.title("Scatter Plot of Photoresistor Values at various Light Levels")
    plt.legend()
    plt.xlabel('Photoresistor Value')
    plt.ylabel('Light Level' + '\n' + '4 = Low  3 = Medium  2 = High  1 = Very High')

    mu, std = norm.fit(diff) # mu is sample mean, std is sample dist
    
    # avg = np.mean(diff)
    # std = np.std(diff, ddof=1)
    # plt.hist(diff, bins=25, density=True)
    
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
    # plt.plot(x, p, 'k', linewidth=2)
    # plt.title("Photoresistor value difference at {} light level".format(light_level))
    plt.show()
    print(shapiro(diff))
    print("N: {}, Mean: {:.02f}, STD: {:.02f}, <0.05%: {:.02f}".format(diff.size, mu, std, lessthan05))
    print()
    
for light_level in ['low', 'medium', 'high', 'vhigh']:
    analyze_photo(light_level)