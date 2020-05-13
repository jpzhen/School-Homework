#! /bin/bash
#set -x
ARTIST=3
ALBUM=4
albumCount=0

echo "<html>"
echo "  <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />"
echo "<body>"
echo "<table border=\"1\">"
echo "  <tr>"
echo "    <th>Artist</th>"
echo "    <th>Album</th>"
echo "    <th>Tracks</th>"
echo "  </tr>"
find Music/ | grep ogg | cut -d "/" -f3 | sort | uniq |
while read artists;
do
    albumCount=$(find Music/ | grep .ogg | grep "$artists" | sort | cut -d "/" -f$ALBUM  | cut -d "/" -f4 | sort | uniq | wc -l)
    n=$albumCount
    find Music/ | grep .ogg | grep "$artists" | sort | cut -d "/" -f4  | cut -d "/" -f$ALBUM | sort | uniq | 
    while read albums;
    do
        echo "  <tr>"
        if [ $n == $albumCount ]
        then
            echo "    <td rowspan=\"$albumCount\">"$artists"</td>"
        fi
        echo "    <td>"$albums"</td>"
        echo "    <td>"
        echo "    <table border=\"0\">"
        find Music/ | grep "/$artists/$albums/" | grep .ogg | sort |
        while read line
        do
            echo "        <tr><td><a href=\""$line"\">"$(echo $line | awk -F "/" '{print $NF}')""
        done
        echo "    </table>"
        echo "    </td>"
        echo "  </tr>"
        ((n--))
    done
done
echo "</table>"
echo "<body>"