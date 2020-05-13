#! /bin/bash 
#Jun Zhen

#cd Music/
echo --Warm Up--

echo Total Tracks: "$(find . | grep .ogg | wc -l)"
printf "\n"
echo Total Artists: $(find . | grep .ogg | cut -d "/" -f3 | sort | uniq | wc -l)
printf "\n"
echo Multi-Genre Artists:
find . | grep .ogg | cut -d "/" -f1-3 | cut -d "/" -f3 | uniq | sort | uniq -d
printf "\n"
echo Multi-Disk Alumbs:
find . | grep disk | cut -d "/" -f4 | sort | uniq
printf "\n"

echo --Detailed Report--
printf "\n"
echo Multi-Genre Artists:
find . | grep .ogg | cut -d "/" -f2,3 | sort | uniq | cut -d "/" -f 2 | sort | uniq -d |
while read artists
do
    echo " " "$artists"
    find . | grep "$artists" | cut -d "/" -f 2 | sort | uniq |
    while read i 
    do
        echo " " " " $i
    done
done

printf "\n"
echo Multi-Disk Albums:
find . | grep disk | cut -d "/" -f3 | sort | uniq |
while read artists;
do
    echo $artists
    find . | grep "$artists"  | grep disk | cut -d "/" -f4 | sort | uniq |
    while read albums;
    do
        echo " " $albums
    done
done


printf "\n"
echo Possible Duplicates Albums:
find . | grep .ogg | cut -d "/" -f4 | uniq | sort | uniq -d | 
while read dAlbums
do 
    echo $dAlbums
    find . | grep "/$dAlbums" | cut -d "/" -f2,3 | sort | uniq | sed 's/\// /' |
    while read i
    do 
        echo " " $i
    done
done
