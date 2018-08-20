library("ggplot2")
args = commandArgs(trailingOnly=FALSE)
if (length(args)==0) {
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
}
path = tail(args, n=1)

#Full Matches
fullMatchData = read.csv(paste(path, "/FullMatches.csv", sep=""))
plot = ggplot(fullMatchData, aes(x=generation, y=matches, color=target)) + labs(title = "Exact Matches") + geom_line()
ggsave(paste(path, "/FullMatches.png", sep=""), height=6, width=10, units="in")

#Char Matches
charMatchData = read.csv(paste(path, "/CharMatches.csv", sep=""))
plot = ggplot(charMatchData, aes(x=generation, y=char_matches, color=target)) + labs(title = "Character Matches") + geom_line()
ggsave(paste(path, "/CharMatches.png", sep=""), height=6, width=10, units="in")

