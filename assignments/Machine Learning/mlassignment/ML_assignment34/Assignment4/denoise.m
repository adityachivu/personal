%   denoise function takes the file names of the actual image and the noisy image as the arguments.
%   Both these images are plotted first.
%   After this the noisy image is denoised using different methods.
%   The resulting images are plotted and their accuracies are calculated by comparing with the original image.
%
%   Method 1: ICMDecoding
%   Method 2: ICMDecoding with 1 restarts
%   Method 3: ICMDecoding with 2 restarts
%   Method 4: ICMDecoding with 3 restarts
%   Method 5: ICMDecoding with 4 restarts
%   Method 6: ICMDecoding with 5 restarts
%   Method 7: Optimal decoding using GraphCut

function denoise(actual,noisy)

% Read actual image
Xactual = dlmread(actual);
Xactual = -Xactual;

% Find number of pixels
Xpix = size(Xactual,1)*size(Xactual,2);

% showing actual image
figure('position',[0,0,1000,1000]);
subplot(3,3,1);
imagesc(Xactual); colormap gray
title('Actual Image');


% Read noisy image
Xnoisy = dlmread(noisy);
Xnoisy = -Xnoisy;

% showing noisy image
subplot(3,3,2);
imagesc(Xnoisy); colormap gray
title('Noisy Image');


% Apply ICM
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Decoding with ICM...\n');
ICMDecoding = UGM_Decode_ICM(nodePot,edgePot,edgeStruct);
Xicm = reshape(ICMDecoding,size(Xnoisy));

Xicm(Xicm==1) = -1;
Xicm(Xicm==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xicm,Xpix)
subplot(3,3,3);
imagesc(Xicm); colormap gray
str = sprintf('ICM\naccuracy = %f',acc);
title(str);


% Apply ICM with 1 restarts
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Decoding with ICM...\n');
ICMDecoding = UGM_Decode_ICMrestart(nodePot,edgePot,edgeStruct, 1);
Xicmr = reshape(ICMDecoding,size(Xnoisy));

Xicmr(Xicmr==1) = -1;
Xicmr(Xicmr==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xicmr,Xpix)
subplot(3,3,4);
imagesc(Xicmr); colormap gray
str = sprintf('ICM with 1 restarts\naccuracy = %f',acc);
title(str);


% Apply ICM with 2 restarts
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Decoding with ICM...\n');
ICMDecoding = UGM_Decode_ICMrestart(nodePot,edgePot,edgeStruct, 2);
Xicmr = reshape(ICMDecoding,size(Xnoisy));

Xicmr(Xicmr==1) = -1;
Xicmr(Xicmr==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xicmr,Xpix)
subplot(3,3,5);
imagesc(Xicmr); colormap gray
str = sprintf('ICM with 2 restarts\naccuracy = %f',acc);
title(str);


% Apply ICM with 3 restarts
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Decoding with ICM...\n');
ICMDecoding = UGM_Decode_ICMrestart(nodePot,edgePot,edgeStruct, 3);
Xicmr = reshape(ICMDecoding,size(Xnoisy));

Xicmr(Xicmr==1) = -1;
Xicmr(Xicmr==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xicmr,Xpix)
subplot(3,3,6);
imagesc(Xicmr); colormap gray
str = sprintf('ICM with 3 restarts\naccuracy = %f',acc);
title(str);


% Apply ICM with 4 restarts
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Decoding with ICM...\n');
ICMDecoding = UGM_Decode_ICMrestart(nodePot,edgePot,edgeStruct, 4);
Xicmr = reshape(ICMDecoding,size(Xnoisy));

Xicmr(Xicmr==1) = -1;
Xicmr(Xicmr==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xicmr,Xpix)
subplot(3,3,7);
imagesc(Xicmr); colormap gray
str = sprintf('ICM with 4 restarts\naccuracy = %f',acc);
title(str);


% Apply ICM with 5 restarts
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Decoding with ICM...\n');
ICMDecoding = UGM_Decode_ICMrestart(nodePot,edgePot,edgeStruct, 5);
Xicmr = reshape(ICMDecoding,size(Xnoisy));

Xicmr(Xicmr==1) = -1;
Xicmr(Xicmr==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xicmr,Xpix)
subplot(3,3,8);
imagesc(Xicmr); colormap gray
str = sprintf('ICM with 5 restarts\naccuracy = %f',acc);
title(str);


% Apply Graph Cut
[nodePot,edgePot,edgeStruct] = getStructs(Xnoisy);

fprintf('Applying Graph Cut Decoding...\n');
OptimalDecoding = UGM_Decode_GraphCut(nodePot,edgePot,edgeStruct);
Xopt = reshape(OptimalDecoding,size(Xnoisy));

Xopt(Xopt==1) = -1;
Xopt(Xopt==2) = 1;

% showing noisy image with accuracy
acc = accuracy(Xactual,Xopt,Xpix)
subplot(3,3,9);
imagesc(Xopt); colormap gray
str = sprintf('Optimal Decoding using Graph Cut\naccuracy = %f',acc);
title(str);