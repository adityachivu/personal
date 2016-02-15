%% Logistic Regression
%

clear ; close all; clc


data = csvread('OnlineNewsPopularity.csv');
X = data(2:30000, 3:60); y = (data(2:30000, 61) > 1400);

[m, n] = size(X);
X = [ones(m, 1) X];

initial_theta = zeros(n + 1, 1);

[cost, grad] = costFunction(initial_theta, X, y);

%  Set options for fminunc
options = optimset('GradObj', 'on', 'MaxIter', 400);

%  Run fminunc to obtain the optimal theta
%  This function will return theta and the cost 
[theta, cost] = ...
	fminunc(@(t)(costFunction(t, X, y)), initial_theta, options);

% Print theta to screen
fprintf('theta found by fminunc\n');

% Compute accuracy on our training set
p = predict(theta, X);

% Computer accuracy on test set
X_test = data(30000:end, 3:60); y_test = (data(30000:end, 61) > 1400);
[mt, nt] = size(X_test);
X_test = [ones(mt, 1) X_test];

p_test = predict(theta, X_test);


fprintf('Train Accuracy: %f\n', mean(double(p == y)) * 100);
fprintf('Test Accuracy: %f\n', mean(double(p_test == y_test)) * 100);

fprintf('Train Precision: %f\n', mean(p) * 100);
fprintf('Test Precision: %f\n', mean(p_test) * 100);

fprintf('Train Recall: %f\n', sum(double(p(y == 1) == 1)) / sum(y) * 100);
fprintf('Test Recall: %f\n', sum(double(p_test(y_test == 1) == 1)) / sum(y_test) * 100);

fprintf('\nProgram paused. Press enter to exit.\n');
pause;

