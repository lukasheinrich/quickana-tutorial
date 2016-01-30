#!/bin/bash
#!/usr/bin/env bash

BRANCH=gh-pages
TARGET_REPO=lukasheinrich/quickana-tutorial-results.git

echo -e "Testing travis-encrypt"
echo -e "$VARNAME"

if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
    echo -e "Starting to deploy to Github Pages\n"
    if [ "$TRAVIS" == "true" ]; then
        git config --global user.email "travis@travis-ci.org"
        git config --global user.name "Travis"
    fi
    #using token clone gh-pages branch
    git clone --quiet --branch=$BRANCH https://${GH_TOKEN}@github.com/$TARGET_REPO results_website &> /dev/null
    #go into directory and copy data we're interested in to that directory

    cd results_website
    rsync -rv --exclude=.git  ../results/* results
    rsync -rv --exclude=.git  ../*.ipynb results
    ipython nbconvert --inplace --execute results/QuickAna\ notebook.ipynb --output results/QuickAna\ notebook.ipynb 

    #add, commit and push files
    git add -f .
    git commit -m "Travis build $TRAVIS_BUILD_NUMBER pushed to Github Pages"
    git push -fq origin $BRANCH &> /dev/null
    echo -e "Deploy completed\n"
fi