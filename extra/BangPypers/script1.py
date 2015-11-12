import numpy as np
import pandas as pd
import matplotlib
from sklearn import preprocessing as pr
from sklearn import linear_model

train_pd = pd.read_csv("data/train.csv")
test_pd = pd.read_csv("data/test.csv")

labels = train_pd.target.values

enc = pr.LabelBinarizer()
binarized_labels = enc.fit_transform(labels)

target = binarized_labels[:,1]
train_pd = train_pd.drop("id", axis=1)
train_pd = train_pd.drop("target", axis=1)

ols = linear_model.LinearRegression( normalize = True, fit_intercept = True)
ols.fit(train_pd, target, n_jobs=-1)

ols_predict = ols.predict(train_pd)


ols_predict_raw = ols_predict.copy()
ols_predict[ols_predict > 0.5] = 1
ols_predict[ols_predict <= 0.5] = 0

ols_model_analysis = pd.concat([pd.Series(target), pd.Series(ols_predict)], axis=1)

ols_model_analysis.columns = ['actual', 'prediction']

true_positives = ols_model_analysis[(ols_model_analysis.actual == 1) & (ols_model_analysis.prediction == 1)].sum()[0]

true_negatives = ols_model_analysis[(ols_model_analysis.actual == 0) & (ols_model_analysis.prediction == 0)].sum()[0]

false_positives = ols_model_analysis[(ols_model_analysis.actual == 0) & (ols_model_analysis.prediction == 1)].sum()[0]

false_negatives = ols_model_analysis[(ols_model_analysis.actual == 1) & (ols_model_analysis.prediction == 0)].sum()[0]

recall = true_positives / (true_positives + false_negatives)
precision = true_positives / (true_positives + false_positives)

from sklearn import metrics
from matplotlib import pyplot

ols_auc = metrics.roc_auc_score(ols_model_analysis.actual, ols_predict_raw)
fpr, tpr, thresholds = metrics.roc_curve(ols_model_analysis.actual, ols_predict_raw)
pyplot.plot(fpr, tpr)
pyplot.plot([0,1],[0,1])

fpr, tpr, thresholds = metrics.roc_curve(ols_model_analysis.actual, ols_model_analysis.prediction)
pyplot.plot(fpr, tpr)
pyplot.plot([0,1],[0,1])



from sklearn.cross_validation import KFold

ols_kf = KFold(n=train_pd.shape[0], n_folds=5, shuffle=True)

ols_cv_metrics = []
for train_index, validate_index in ols_kf:
    
    sample_train, sample_validate = train_pd.loc[train_index], train_pd.loc[validate_index]
    sample_train_target, sample_validate_target = target[train_index], target[validate_index]
    
    ols = linear_model.LinearRegression(normalize=True)
    ols.fit(sample_train, sample_train_target, n_jobs=-1)
    ols_sample_predict = ols.predict(sample_validate)
    
    ols_predict_raw = ols_sample_predict.copy()
    ols_sample_predict[ols_sample_predict > 0.5] = 1
    ols_sample_predict[ols_sample_predict <= 0.5] = 0

    ols_model_analysis = pd.concat([pd.Series(sample_validate_target), pd.Series(ols_sample_predict)], axis=1)
    ols_model_analysis.columns = ['actual', 'prediction']

    true_positives = ols_model_analysis[(ols_model_analysis.actual == 1) & (ols_model_analysis.prediction == 1)]\
                        .sum()[0]
    true_negatives = ols_model_analysis[(ols_model_analysis.actual == 0) & (ols_model_analysis.prediction == 0)]\
                        .sum()[0]
    false_positives = ols_model_analysis[(ols_model_analysis.actual == 0) & (ols_model_analysis.prediction == 1)]\
                        .sum()[0]
    false_negatives = ols_model_analysis[(ols_model_analysis.actual == 1) & (ols_model_analysis.prediction == 0)]\
                        .sum()[0]

    precision = true_positives / (true_positives + false_positives)
    recall = true_positives / (true_positives + false_negatives)

    ols_auc = metrics.roc_auc_score(ols_model_analysis.actual, ols_model_analysis.prediction)
    ols_f1 = 2*true_positives / (2*true_positives + false_positives + false_negatives)
    
    ols_cv_metrics.append((precision, recall, ols_auc, ols_f1)) 
    
ols_metric_pd = pd.DataFrame(ols_cv_metrics).mean()

ols_metrics_pd = pd.DataFrame(pd.DataFrame(ols_metric_pd).T)
ols_metrics_pd.columns=['precision', 'recall', 'auc', 'f1']
print ols_metrics_pd


from sklearn.tree import DecisionTreeClassifier, export_graphviz
from sklearn.cross_validation import train_test_split
dtc = DecisionTreeClassifier(max_depth = 8)

dtc.fit(train_pd, target)

dtc_cv_metric = cross_validate(dtc, train_pd, target)

dtc_metrics = pd.DataFrame(dtc_cv_metric).mean()
dtc_metrics_pd = pd.DataFrame(pd.DataFrame(dtc_metrics).T)
dtc_metrics_pd.columns=['precision', 'recall', 'auc', 'f1']
print dtc_metrics_pd

export_graphviz(dtc, feature_names=train_pd.columns)
from IPython.display import Image

Image('tree.png', unconfined=True)