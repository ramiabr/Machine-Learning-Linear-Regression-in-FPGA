
% - Use Linear regression algorithm (Gradient descent) to fit housing prices in San Luis Obispo county. 
% - Fit the data based on one feature(size of house). 
% - After fitting the values we get a equation yhat = w0+x*w1, where if we plugin sq feet x it gives the price as output 
               
% Description of your Solution
% - In this matlab solution I have use gradient descend algorithm to calculate the weights 
% - The learning rate is set to 0.8 and 2000 iterations are done to calculate weights
% - Final weight values computed are 

%  1.0e+05 *
  
%  [         ]
%  | -0.0992 |
%  |  2.6912 |
%  [         ]

% - The weight values don't change after 2000 iterations, it remains the same even if I run till 10,000 iterations 
% - It also matches OLS results 



clear all; close all;

X=dlmread('housing_price_data.dat');
F=sortrows([X(:,5) X(:,2)]);

figure; scatter(F(:,1), F(:,2));
title('Scatter plot of housing prices');
xlabel('Size in square Feet');
ylabel('Price');  

F=F(25:600,:); % size 576x2
%seed = 100; rand('seed', seed); randn('seed', seed);

 X=F(:,1);
normalize = max(X)-min(X);
 
X = X/normalize;
X = [repmat(1,length(F),1) X]; % = [1 X]

y=F(:,2);
%normalize_y = max(y) - min(y); 
%y = y/normalize_y; 

w = rand(2,1); % size w is 2x1

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parameters
% X = 576x2 [1 size_of_house]
% y = 576x1
% w = 2x1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialize learning rate

nu = 0.8; % play with this parameter
mse = [];


for k = 1:2000
    fx = X * w;
    sq = (fx-y).^2;
    mse_var = sum(sq) / (2 * 576);
    mse = [ mse; k, mse_var];

    jw0 = sum(((fx-y).* X(:,1)));
    jw1 = sum(((fx-y).* X(:,2))); 
    
    jw0 = jw0 / 576; 
    jw1 = jw1 / 576; 

    w(1,1) = w(1,1) - nu * jw0;
    w(2,1) = w(2,1) - nu*  jw1; 
end

yhat = X*w; 
figure; hold off; 
scatter(X(:,2)*normalize,y, 50, '.'); hold; 
plot(X(:,2)*normalize,yhat,'r'); 
xlabel('Size in square Feet');
ylabel('Price'); 

figure; scatter(mse(:,1), mse(:,2));
%hold; 
%plot(mse(:,1), mse(:,2))
%figure ; plot(mse)
title('Mean Square Error');
xlabel('Iterations'); ylabel('Error');  