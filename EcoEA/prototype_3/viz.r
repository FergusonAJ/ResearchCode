library("ggplot2")
args = commandArgs(trailingOnly=FALSE)
if (length(args)==0) {
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
}
path = tail(args, n=1)

#Score
scoreData = read.csv(paste(path, "/Score.csv", sep=""))
plot = ggplot(scoreData, aes(x=generation, y=score)) + labs(title = "Score") + geom_line()
ggsave(paste(path, "/Score.png", sep=""), height=6, width=10, units="in")

#Tasks (overall)
taskOData = read.csv(paste(path, "/TasksOverall.csv", sep=""))
plot = ggplot(taskOData, aes(x=generation, y=count, color=task)) + labs(title = "Tasks") + geom_line()
ggsave(paste(path, "/TasksOverall.png", sep=""), height=6, width=10, units="in")

#Tasks (best)
taskBData = read.csv(paste(path, "/TasksBest.csv", sep=""))
plot = ggplot(taskBData, aes(x=generation, y=count, color=task)) + labs(title = "Tasks") + geom_line()
ggsave(paste(path, "/TasksBest.png", sep=""), height=6, width=10, units="in")
