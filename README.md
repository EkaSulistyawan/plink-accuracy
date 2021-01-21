# plink-accuracy
This repo is intended to calculate PLINK 1.9 accuracy through simple Hap to Hap comparison. Tested on Windows.
# Basics
The basic concept of the accuracy calculation is based on ground-truth and imputed comparison.

# Directory
-- -- data <br>
-- -- cpp-sources <br>
-- -- script <br>
-- -- reference <br>
-- plink (executable) <br>
-- evaluator (executable) <br>
-- random_generator (executable) <br>
-- collective_evaluation (batch) <br>
-- run (batch) <br>
### Directory Explanation
* `data` contains processed data
* `cpp-sources` , you may compile this and put the executable one folder before (evaluator and random_generator executable)
* `random_generator` used to create dataset based on random deletion in the reference dataset,
* `evaluator` used to calculate accuracy based on simple Hap to Hap comparison,
* `script` contains PLINK script to execute 
  * Filter
  * Merge
  * Impute
* `reference` , reference panel [here](http://zzz.bwh.harvard.edu/plink/res.shtml#hapmap)
* `collective_evaluation` , performin `run` for several rate of deletion
* `run` , performing single test accuracy
* PLINK 1.9 , downloaded on link below,
# Workflow
1. Put reference panel (Binary PLINK format) in the `reference`,
2. Make sure Filter `script` match the reference file name,
3. Try performing `run {rate of deletion}` , the rate of deletion is the percentage amount of genotype deleted for each marker (0.0 - 1.0),
4. Perform `collective_evaluation`
5. Data will output `summary.csv` for each different parameter of `run`
# Additional Resources 
[Plink 1.9](http://zzz.bwh.harvard.edu/plink/), including
1. Plink 1.9 EXECUTABLE file
2. Imputation tutorial
3. Brief concept explanation for the imputation @ Proxy-association section,
4. Reference data (this project used filtered HapMap CEU)
