library(ggplot2)

rm(list=ls())
setwd('~/Documents/School/FA18/EC/TermProject/work/main/viz/tests')

job_id <- '2977790'

scrubbed_data <- read.csv(paste(sep='', './', job_id, '_SCRAPED.csv'))
write.csv(x = scrubbed_data, file = paste(sep='', './', job_id, '_SCRUBBED.csv'))