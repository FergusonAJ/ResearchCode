library(ggplot2)

rm(list=ls())
setwd('~/Research/CCGA/viz/out')

job_id <- '6759876'

hasBeenDone <- length(which(list.files() == paste(sep='', job_id, '_SCRUBBED.csv'))) > 0

if(hasBeenDone){
  print('Already processed! Loading from .csv')
  scrubbed_data <- read.csv(paste(sep='', job_id, '_SCRUBBED.csv'))  
}else{
  print('Generating from scratch!')
  data <- read.csv(paste(sep='', './', job_id, '_SCRAPED.csv'))
  scrubbed_data <- data.frame(matrix(ncol=5, nrow=0))
  for(arr_id in 1:50){
    for(gen in 0:49){
      if(nrow(data[data$arr_id == arr_id & data$gen == gen,]) > 0){
        min <- min(data[data$arr_id == arr_id & data$gen == gen,]$value)
        max <- max(data[data$arr_id == arr_id & data$gen == gen,]$value)
        mean <- mean(data[data$arr_id == arr_id & data$gen == gen,]$value)
        scrubbed_data <- rbind(scrubbed_data, c(arr_id, gen, min, max, mean))
      }
    }
    print(arr_id)
  }
  colnames(scrubbed_data) <- c('arr_id', 'gen', 'min', 'max', 'avg')
  
  write.csv(x = scrubbed_data, file = paste(sep='', './', job_id, '_SCRUBBED.csv'))
}

max_df <- data.frame(matrix(ncol=4, nrow=0))
min_df <- data.frame(matrix(ncol=4, nrow=0))
avg_df <- data.frame(matrix(ncol=4, nrow=0))
for(gen in 0:49){
  t <- t.test(scrubbed_data[scrubbed_data$gen == gen, ]$min)
  min_df <- rbind(min_df, c(gen, t$conf.int[1], t$estimate, t$conf.int[2]))
  t <- t.test(scrubbed_data[scrubbed_data$gen == gen, ]$max)
  max_df <- rbind(max_df, c(gen, t$conf.int[1], t$estimate, t$conf.int[2]))
  t <- t.test(scrubbed_data[scrubbed_data$gen == gen, ]$avg)
  avg_df <- rbind(avg_df, c(gen, t$conf.int[1], t$estimate, t$conf.int[2]))
}
colnames(max_df) <- c('gen', 'lower', 'mean', 'upper')
colnames(min_df) <- c('gen', 'lower', 'mean', 'upper')
colnames(avg_df) <- c('gen', 'lower', 'mean', 'upper')
ggplot(max_df, aes(x=gen)) +
  geom_ribbon(data=max_df, aes(x=gen, ymin=lower, ymax=upper), fill = 'green', alpha=0.15) +
  geom_ribbon(data=min_df, aes(x=gen, ymin=lower, ymax=upper), fill = 'red', alpha=0.15) +
  geom_ribbon(data=avg_df, aes(x=gen, ymin=lower, ymax=upper), fill = 'blue', alpha=0.15) +
  geom_line(data=max_df, aes(x=gen, y=mean), color='darkgreen') +
  geom_line(data=min_df, aes(x=gen, y=mean), color='darkred') +
  geom_line(data=avg_df, aes(x=gen, y=mean), color='darkblue') + 
  ylab('Fitness') + 
  xlab('Generation')
ggsave(filename = paste(sep='', './', job_id, '.png'))

