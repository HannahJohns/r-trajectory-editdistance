#tracks are list of data frames

tracks <- readTracks("../DATA/tracks25Aug.txt")

# track1, track2 and track3 are data frames

track1 = data.frame(x = c(1,2,3), y = c(2,3,4))
track2 = data.frame(x = c(10,20,3), y = c(2,3,4))
track3 = tracks[[1]]
track4 = tracks[[2]]

# parameters
spacingX <- 10
spacingY <- 10
time_spacing <- 1.75
row_size <- 10

editdist(track1, track2, spacingX, spacingY, time_spacing)


