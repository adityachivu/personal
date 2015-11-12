function acc = accuracy(Xactual,Xdenoised,Xpix)

% Find pixel matches
Xrestored = sum(sum(Xactual == Xdenoised));

% Calculate accuracy
acc = (Xrestored/Xpix) * 100;