# Jun Zhen
# CSS 436 Cloud Computing
# 02-16-20
# ass3Backup.py - Take in folder name as an argument and make a backup to the cloud of the specified directory
# to AWS and maintain the file structure

import boto3
import logging
from botocore.exceptions import ClientError
import hashlib
import os
import sys
import time

# Global variables
s3 = boto3.resource("s3")
bucketName = "1950386css436prog3"
regionName = "us-west-2"
currentDir = "./"

# Create bucket
def makeBucket(bucket_name, region):
    try:
        s3_client = boto3.client('s3', region)
        location = {'LocationConstraint': region}
        s3_client.create_bucket(Bucket=bucket_name, CreateBucketConfiguration=location)
    except ClientError as e:
        logging.error(e)
        return False
    return True

#Print out all the buckets in s3
def printAllBuckets():
    for bucket in s3.buckets.all():
        print("Bucket: ", bucket.name)
        print("--------")
        for key in bucket.objects.all():
            print(key.key)
        print("")
 

#Helper function for getLocalChecksum, return file.read()
def readFile(fileName):
    with fileName:
        return fileName.read()

#Get the checksum of the file passed in
def getLocalChecksum(fileName):
        return hashlib.md5(readFile(open(fileName, "rb"))).hexdigest()

# Local into the s3 bucket and find its checksum value stored as metadata
def getS3Checksum(fileName):
    return(s3.Object(bucketName,fileName).get()["Metadata"]["sumvalue"])

# Main function that utitlize os.walk to backup files and folder into aws s3
def Backup(path):
    transfer = boto3.client("s3")
    for dirName, subdirList, fileList in os.walk(path):
        # print('Found directory: %s' % dirName)
        for fname in fileList:
            #Full path
            fullpath = os.path.join(dirName,fname)
            #key gets rid of the root ("./") directory
            key = fullpath 
            #Get the check sum of the file we going to store in s3
            checksumValue = getLocalChecksum(fullpath)
            # Only insert if s3 and local don't have matching files
            if (checkObjExists(key)):
                if (checksumValue != getS3Checksum(key)):
                    print("Updating Backing up:", fname)
                    transfer.upload_file(key, Key=key, ExtraArgs= {"Metadata":{"sumValue": checksumValue}}, Bucket=bucketName)
            else:
                print("Backing up:", fname)
                transfer.upload_file(key, Key=key, ExtraArgs= {"Metadata":{"sumValue": checksumValue}}, Bucket=bucketName)
                
# Check if object exists 
def checkObjExists(key):
    try:
        s3.Object(bucketName, key).load()
    except ClientError as e:
        return False
    return True

# Main Fuction
if __name__ == "__main__":
    print("BACKING UP")
    try:
        s3.meta.client.head_bucket(Bucket=bucketName)
        print("Bucket %s Already Exists" % (bucketName))
    except ClientError:
        if (makeBucket(bucketName, regionName)):
            print("Successful Creating Bucket: %s!!!" % (bucketName))
        else:
            print("Unsuccessful Creating Bucket: %s... " % (bucketName))
        
    path = sys.argv[1] 
    Backup(path)

    # This might crash due to the time it takes for aws to create bucket and load objects if that's the case please run 
    # it again or uncommon the sleepe timer during the first run.
    printAllBuckets()
