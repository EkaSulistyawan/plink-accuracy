@echo off
:: echo "Filtering ... "
:: discomment this to perform filtering
:: plink --script script\filter.sc
echo "Random test creator"
randomgen.exe data\filtered.ped data\test.ped %1
echo "Merging ... "
plink --script script\merger.sc
echo "Imputing ... "
plink --script script\imputer.sc
echo "evaluating ... "
evaluator.exe data\merged-test.ped data\imputed.ped