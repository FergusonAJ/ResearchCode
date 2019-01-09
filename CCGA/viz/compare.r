library(ggplot2)

rm(list=ls())
setwd('~/Documents/School/FA18/EC/TermProject/work/main/viz/tests')

#RepStat - Normal
#job_id_arr <- c('./control/2573653', './classic/2574114', './quads/2574204', './stripes/2574265')

#Match - Normal
#job_id_arr <- c('./control/2656170', './classic/2656221', './quads/2656277', './stripes/2656327')

#Match - Limited
#job_id_arr <- c('./control/2656812', './classic/2656862', './quads/2656912', './stripes/2656962')

#Gliders - Normal
#job_id_arr <- c('./control/final/2861373', './classic/final/2861376', './quads/final/2861477', './stripes/final/2861480')

#RepStat - Limited
#job_id_arr <- c('./control/final/2862882', './classic/final/2862884', './quads/final/2862885', './stripes/final/2862889')

#Gliders - Limited
#job_id_arr <- c('./control/final/2877076', './classic/final/2877126', './quads/final/2877177', './stripes/final/2877178')

#Match - Cols
#job_id_arr <- c('./control/new_match/2949115', './classic/new_match/2949165', './quads/new_match/2949166', './stripes/new_match/2949167')

#Match - Checker
#job_id_arr <- c('./control/new_match/2950982', './classic/new_match/2950984', './quads/new_match/2950986', './stripes/new_match/2950987')

#Match - Cols - Limited
#job_id_arr <- c('./control/2977491', './classic/2977493', './quads/2977593', './stripes/2977595')

#Match - Checker - Limited
job_id_arr <- c('./control/2977790', './classic/2977840', './quads/2977841', './stripes/2977842')


show_max <- T
show_min <- F
show_avg <- T
names <- c('Control', 'Classic', 'Quads', 'Stripes')

factors <- factor(c('Control', 'Classic', 'Quads', 'Stripes'))

ggp <- NA
for(id in 1:length(job_id_arr)){
  scrubbed_data <- read.csv(paste(sep='', job_id_arr[id], '_SCRUBBED.csv'))  
  
  max_df <- data.frame(matrix(ncol=5, nrow=0))
  min_df <- data.frame(matrix(ncol=5, nrow=0))
  avg_df <- data.frame(matrix(ncol=5, nrow=0))
  for(gen in 0:49){
    t <- t.test(scrubbed_data[scrubbed_data$gen == gen, ]$min)
    min_df <- rbind(min_df, c(gen, t$conf.int[1], t$estimate, t$conf.int[2], id))
    t <- t.test(scrubbed_data[scrubbed_data$gen == gen, ]$max)
    max_df <- rbind(max_df, c(gen, t$conf.int[1], t$estimate, t$conf.int[2], id))
    t <- t.test(scrubbed_data[scrubbed_data$gen == gen, ]$avg)
    avg_df <- rbind(avg_df, c(gen, t$conf.int[1], t$estimate, t$conf.int[2], id))
  }
  colnames(max_df) <- c('gen', 'lower', 'mean', 'upper', 'color')
  colnames(min_df) <- c('gen', 'lower', 'mean', 'upper', 'color')
  colnames(avg_df) <- c('gen', 'lower', 'mean', 'upper', 'color')
  if(length(ggp) <= 1 && is.na(ggp)){
    ggp <- ggplot(max_df, aes(x=gen)) +
    ylab('Fitness') + 
    xlab('Generation')
  }
  col <- id + 1
  if(show_max){
    ggp <- ggp + geom_ribbon(data=max_df, aes(x=gen, ymin=lower, ymax=upper, fill = factor(color)) , alpha=0.15)
    ggp <- ggp + geom_line(data=max_df, aes(x=gen, y=mean, color=factor(color)))
  }
  if(show_min){
    ggp <- ggp + geom_ribbon(data=min_df, aes(x=gen, ymin=lower, ymax=upper, fill = factor(color)), alpha=0.15)
    ggp <- ggp + geom_line(data=min_df, aes(x=gen, y=mean, color=factor(color)))
  }
  if(show_avg){
    ggp <- ggp + geom_ribbon(data=avg_df, aes(x=gen, ymin=lower, ymax=upper, fill = factor(color)), alpha=0.15)
    ggp <- ggp + geom_line(data=avg_df, aes(x=gen, y=mean, color=factor(color))) 
  }
}
ggp <- ggp + scale_fill_manual(labels=names, values=c(2,3,4,6), name='Treatment')
ggp <- ggp + scale_color_manual(labels=names, values=c(2,3,4,6), name='Treatment')
#ggp <- ggp + ylim(c(0,1))
ggp
ggsave(filename = './tmp.png', width=8, height=8)
