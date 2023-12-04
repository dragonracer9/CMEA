% Plots the linear regression but doesn't add pretty cats due to MATLAB being very serious.

Y = [ 6.5 , 7.2 , 7.3 , 7.6 , 7.7 , 7.9 , 7.9 , 7.9 , 7.9 , 8.0 , 8.3, 8.5 , 8.6 , 8.8 , 8.8];

X = [2 , 2.2 , 2.4 , 2.2 , 2.6 , 2.2 , 2.4 , 2.4 , 2.5 , 2.7 , 2.6 , 2.2 , 2.5 , 2.5 , 2.5 ];

hold on
scatter(X, Y, 'p')


x = linspace(min(X), max(X),100);
regression = load("coeffs_regression.txt");
plot(x, regression(2)*x + regression(1), '--');
xlabel("Body weight (kg)");
ylabel("Mass of heart (g)");

legend('Observed data', 'Regression')

  
