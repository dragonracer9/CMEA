errors = load('series0_1_d_errors.txt');
numberOfIntervals = load('series0_1_d_numbers.txt');

loglog(numberOfIntervals, errors, '*-');
title('Error plot for ex. 0.1d)')
xlabel('n')
ylabel('|I(f)-I_n(f)|')
hold on
loglog(numberOfIntervals, numberOfIntervals.^(-2), '--')

legend('|I_n(f)-I(f)|', 'O(n^{-2})')
grid on
grid minor
