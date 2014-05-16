---
layout: post
title: GitHub Steps
tags: github iniciante newbie
---

*GitHub Steps*

-----



> **//TODO** Description of GitHub first steps

# GitHub

> Still trying to find out what this is



## First Steps(Web)

### Create New File

**1. Create/Open Repository**

**2. Create new file**: Over your-repository.io/_genericfolder/

**(Opcional) Use extension *.md for fancy layout**

    **Error**: Line break  
    When you do want to insert a line break using Markdown, you end a line with two or more spaces, then type return.  
    http://daringfireball.net/projects/markdown/syntax#p

    **Error**: Create folder
    Como se cria pastas???

## First Steps(Terminal)

### Create New File

**1. Create a new repository on the command line**
$ touch README.md  
$ git init  
$ git add README.md  
$ git commit -m "first commit"  
$ git remote add origin https://github.com/rafaelsanchezsouza/steps.git  
$ git push -u origin master  

    **Error**: "remote origin already exists on git push to new repository"  
    http://stackoverflow.com/questions/1221840/remote-origin-already-exists-on-git-push-to-new-repository  
    "origin" is the local name of the remote repository  

    **Error**: Repository not found  
    After above procedure, pushing repository wasn's succeded  

**2. Push an existing repository from the command line**  
$ git remote add origin https://github.com/rafaelsanchezsouza/steps.git  
$ git push -u origin master  

