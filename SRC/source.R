

lappend <- function(lst, pos, obj) {
  lst[[pos]] <- obj
  return(lst)
}


readTracks <-
  function(filepath, totalNumTracks = 100)
  {
    day = read.table(filepath, header=T, sep = "\t")
    
    #totalNumTracks <- day$x[day$track == "length"]
    #totalNumTracks <- 100
    
    if(is.null(totalNumTracks)){
      files[dayNumber]
    }
    
    tracks<-list()
    
    trackNumber = 1
    #Check totalNumTracks it's one more 
    while(trackNumber <= totalNumTracks){
      track <- data.frame(x = day$x[day$track == trackNumber], y = day$y[day$track==trackNumber])
      tracks = lappend(tracks, trackNumber , track)
      
      trackNumber = trackNumber + 1
    }
    return (tracks)
  }

traj2RawStr <- function(track, spacingX, spacingY, tilesOnX) {
  str_list = list()
  tile = 0
  
  i <- 1
  
  while(i <= length(track$x)) {
    
    temp = (floor((track$y[i] / spacingY))*tilesOnX + floor((track$x[i] / spacingX)))
    
    str_list = lappend(str_list, i, temp)
    
    i <- i + 1
  }
  
  return(str_list)
}

editdist <-
  function(track1, track2, spacingX, spacingY, time_spacing = 1.0)
  {
    string1 <- traj2RawStr(track1, spacingX, spacingY, row_size)
    string2 <- traj2RawStr(track2, spacingX, spacingY, row_size)
    #result <- 1.0
    
    dyn.load("./editDistance2.so")  # this should refer to compiled c code
    
    returned_data <- .C("editDistance", as.integer(string1), as.integer((length(string1))), as.integer(string2), as.integer((length(string2))), 
                       as.integer(row_size), as.numeric(time_spacing), as.numeric(integer(1)))
    
    return (returned_data[[7]])
    
  }