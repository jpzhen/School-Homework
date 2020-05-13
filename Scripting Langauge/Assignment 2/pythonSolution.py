#!/usr/bin/python3
import fileinput

#parsing the data,
#store the artist and it's album into a dict
#Store all the information give by input into a matrix
uniqArtistAlbum = dict()
lineList = [] #{ 0: Music, 1: Genre, 2: Artist, 3: Album, 4: Song, 5: Song Path }
parsedMatrix = []
for line in fileinput.input():
    lineList = line.strip().split("/")
    if(len(lineList) == 5 and (lineList[len(lineList)-1][:-1] != "disk")): #get rid of lines that have no songs
        lineList.append(line.strip())
        parsedMatrix.append(lineList)
        artist = lineList[2]
        album = [lineList[3]]
        if(artist in uniqArtistAlbum):
            if(lineList[3] not in uniqArtistAlbum[artist]):
                uniqArtistAlbum[artist].append(lineList[3])
        else:
            uniqArtistAlbum[artist] = album
    elif(len(lineList) == 6): #get the line that have disks
        lineList.append(line.strip())
        parsedMatrix.append(lineList)
        artist = lineList[2]
        album = [lineList[3]]
        if(artist in uniqArtistAlbum):
            if(lineList[3] not in uniqArtistAlbum[artist]):
                uniqArtistAlbum[artist].append(lineList[3])
        else:    
            uniqArtistAlbum[artist] = album

#Generating the data for html
print('<html>')
print('  <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />')
print('<body>')
print('<table border=\"1">')
print('  <tr>')
print('    <th>Artist</th>')
print('    <th>Album</th>')
print('    <th>Tracks</th>')
print('  </tr>')
parsedMatrix.sort(key=lambda tup: (tup[2], tup[5]))
#Loop each artist and search for album by that artist and print
for artists in sorted(uniqArtistAlbum):
    uniqArtistAlbum[artists].sort()
    albCount = len(uniqArtistAlbum[artists])
    n = albCount
    for albums in uniqArtistAlbum[artists]:
        print('  <tr>')
        if(n == albCount): #print rowspan header only for the first album
            print('%s%d%s%s%s' %('    <td rowspan=\"', albCount, '\">', artists, '</td>' ))
        print('%s%s%s' % ('    <td>',albums,'</td>'))
        print('%s' % ('    <td>'))
        print('%s' % ('      <table border=\"0\">'))
        for i in range(0, len(parsedMatrix)):
            if(parsedMatrix[i][2] == artists and parsedMatrix[i][3] == albums ):
                songPath = parsedMatrix[i][len(parsedMatrix[i])-1]
                songName = parsedMatrix[i][len(parsedMatrix[i])-2]
                print ('%s%s%s%s%s%s' %('        <tr><td><a href=', '\"', songPath, '\">', songName, '</a><td></tr>'))
        print('%s' % ('      </table>'))
        print('%s' % ('    </td>'))
        print('  </tr>')
        n-=1
print('</table>')
print('<body>')