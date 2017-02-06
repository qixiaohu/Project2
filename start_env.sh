#!/bin/bash
#启动tracker
fdfs_trackerd /etc/fdfs/tracker.conf
#启动storage
fdfs_storaged /etc/fdfs/storage.conf
