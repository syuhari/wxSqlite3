#!/bin/sh

commandline()
{
sleep 1; echo ".output ../Resources/data/data.sql"
sleep 1; echo ".dump"
sleep 1; echo ".exit"
}

commandline | sqlite3 ../Resources/data/data.sqlite
