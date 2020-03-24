# Jun Zhen
# CSS 436 Cloud Computing
# 02-16-20
# ass3Backup.py - Take in folder name as an argument and restore from the cloud the specified directory from AWS. The
# directory structure of the files will be keep intact.

import os 
import boto3
import sys
from botocore.exceptions import ClientError
import logging

# Global variable
bucketName = "1950386css436prog3"
s3 = boto3.resource('s3')

# Check if object exists 
def checkObjExists(key):
    try:
        s3.Object(bucketName, key).load()
    except ClientError as e:
        return False
    return True

# Open up the bucket and using the module os to recursively tranverse and download the files
def Restore(directoryName):
    bucket = s3.Bucket(bucketName) 
    for obj in bucket.objects.filter(Prefix = directoryName):
        if not os.path.exists(os.path.dirname(obj.key)):
            os.makedirs(os.path.dirname(obj.key))
        bucket.download_file(obj.key, obj.key)

if __name__ == "__main__":
    # Check if bucket exists before restoring
    try:
        s3.meta.client.head_bucket(Bucket=bucketName)
        Restore(sys.argv[1])
    except ClientError:
        print("BUCKET DOES NOT EXISTS")
