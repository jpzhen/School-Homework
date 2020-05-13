I implement the solution with python and pure bash with little bit help from awk. At first
Both solution had the same logic. Find all uniq artists, use that list to find their albums,
and for each song print their path and attach html tags. 

My solution to generate the html file was very slow. It has to do with my solution constantly using
find and locate the artists, albums, and songs. This was easier to implement because of bash utilities
that get what i wanted without appling any logical checks. 

With my python solution, I use find <dirName>/ and piped into the python script. This solution was much faster
in term of real life time. For the python script, I stored the input from find to a matrix. With the matrix holding all information,
I was able to apply the same logic of find artist then album etc. This script was much heavier on the number of line side.
Implementing the solution in python was much harder than bash because of my small experience with python and I don't have access to bash utilities.

At first I wanted to do it in bash and perl, but perl end up being too diffcult to understand, so i switched to python. I do not know python much
but the language is very straightfoward and the syntax are much easier to understand than perl. I already understood what I needed to do from the solution 
I did in bash, I just need to apply the same way with python. 