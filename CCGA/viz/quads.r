args <- commandArgs(trailingOnly=T)
if(length(args) == 0){
    print('You must pass the idStr!')
    quit()
}

idStr <- args[1]

setwd('~/Documents/School/FA18/EC/TermProject/work/main/viz')
library(ggplot2)


ic1_data <- read.csv(paste('../output/quads_ic1', idStr, '.csv', sep=''))
numGens = max(ic1_data$gen)
ic1_df <- data.frame(matrix(nrow=numGens, ncol=4))
colnames(ic1_df) <- c('min', 'avg', 'max', 'gen')
for(i in 1:numGens){
  ic1_df[i,'min'] = min(ic1_data[ic1_data$gen == i-1,]$value)
  ic1_df[i,'avg'] = ave(ic1_data[ic1_data$gen == i-1,]$value)[1]
  ic1_df[i,'max'] = max(ic1_data[ic1_data$gen == i-1,]$value)
  ic1_df[i,'gen'] = i
}

ic2_data <- read.csv(paste('../output/quads_ic2', idStr, '.csv', sep=''))
numGens = max(ic2_data$gen)
ic2_df <- data.frame(matrix(nrow=numGens, ncol=4))
colnames(ic2_df) <- c('min', 'avg', 'max', 'gen')
for(i in 1:numGens){
  ic2_df[i,'min'] = min(ic2_data[ic2_data$gen == i-1,]$value)
  ic2_df[i,'avg'] = ave(ic2_data[ic2_data$gen == i-1,]$value)[1]
  ic2_df[i,'max'] = max(ic2_data[ic2_data$gen == i-1,]$value)
  ic2_df[i,'gen'] = i
}

ic3_data <- read.csv(paste('../output/quads_ic3', idStr, '.csv', sep=''))
numGens = max(ic3_data$gen)
ic3_df <- data.frame(matrix(nrow=numGens, ncol=4))
colnames(ic3_df) <- c('min', 'avg', 'max', 'gen')
for(i in 1:numGens){
  ic3_df[i,'min'] = min(ic3_data[ic3_data$gen == i-1,]$value)
  ic3_df[i,'avg'] = ave(ic3_data[ic3_data$gen == i-1,]$value)[1]
  ic3_df[i,'max'] = max(ic3_data[ic3_data$gen == i-1,]$value)
  ic3_df[i,'gen'] = i
}

ic4_data <- read.csv(paste('../output/quads_ic4', idStr, '.csv', sep=''))
numGens = max(ic4_data$gen)
ic4_df <- data.frame(matrix(nrow=numGens, ncol=4))
colnames(ic4_df) <- c('min', 'avg', 'max', 'gen')
for(i in 1:numGens){
  ic4_df[i,'min'] = min(ic4_data[ic4_data$gen == i-1,]$value)
  ic4_df[i,'avg'] = ave(ic4_data[ic4_data$gen == i-1,]$value)[1]
  ic4_df[i,'max'] = max(ic4_data[ic4_data$gen == i-1,]$value)
  ic4_df[i,'gen'] = i
}



ruleset_data <- read.csv(paste('../output/quads_ruleset', idStr, '.csv', sep=''))
numGens = max(ruleset_data$gen)
ruleset_df <- data.frame(matrix(nrow=numGens, ncol=4))
colnames(ruleset_df) <- c('min', 'avg', 'max', 'gen')
for(i in 1:numGens){
  ruleset_df[i,'min'] = min(ruleset_data[ruleset_data$gen == i-1,]$value)
  ruleset_df[i,'avg'] = ave(ruleset_data[ruleset_data$gen == i-1,]$value)[1]
  ruleset_df[i,'max'] = max(ruleset_data[ruleset_data$gen == i-1,]$value)
  ruleset_df[i,'gen'] = i
}

ggplot(data = ruleset_df, aes(x=gen, y=max)) + 
  geom_line(color='green') +
  geom_line(aes(x=gen, y=min), color='red') + 
  geom_line(aes(x=gen, y=avg), color='blue') +
  geom_line(data = ic1_df, aes(x=gen, y=max), color='green', linetype='dashed') +
  geom_line(data = ic1_df, aes(x=gen, y=min), color='red', linetype='dashed') +
  geom_line(data = ic1_df, aes(x=gen, y=avg), color='blue', linetype='dashed') +
  xlab('Generation') + 
  ylab('Fitness') +
  ggtitle('Fitness over time for "Quads" treatment')

ggsave(paste(sep='', '../output/quads_', idStr, '.png'))
