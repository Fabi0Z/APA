#!/usr/bin/bash

STUDENT_ID="251489" # Default value for STUDENT_ID

if [ -z "$1" ]; then # Check if the submission parameter exist
    echo "No submission number provided"
    echo "Usage: consegna.sh [SUBMISSION_NUMBER] [STUDENT_ID]"
    exit 1
elif [ -z "$2" ]; then # Check if the STUDENT_ID parameter exist
    SUBMISSION_NUMBER=$1
    echo "No student ID provided, using the default" $STUDENT_ID
    echo
else
    SUBMISSION_NUMBER=$1
    STUDENT_ID=$2
fi

STUDENT_ID="s"$STUDENT_ID                   # Assign correct value to STUDENT_ID
FILENAME=consegne/"$STUDENT_ID"_"$1".tar.gz # Save filename value

case "$SUBMISSION_NUMBER" in
1)
    LAB_ARRAY=(L01 L02 L03)
    ;;
2)
    LAB_ARRAY=(L04 L05 L06)
    ;;
3)
    LAB_ARRAY=(L07 L08 L09)
    ;;
4)
    LAB_ARRAY=(L10 L11 L12)
    ;;
*)
    echo "Invalid SUBMISSION_NUMBER"
    exit 2
    ;;
esac

TEMP_DIR="temp_"$(date +%s) # Temp dir name
mkdir $TEMP_DIR             # Make a temp directory

for lab in "${LAB_ARRAY[@]}"; do # For every LAB in lab array
    cp -r $lab $TEMP_DIR    # Copy SUBMISSION_NUMBER files to temp dir
done

find $TEMP_DIR -type f -name '*.pdf' -delete # Delete all PDF
find $TEMP_DIR -type f -name '*.o' -delete # Delete all libraries

echo "Compressing files..."
cd $TEMP_DIR
tar -czvf ../"$FILENAME" *
cd ..

echo
echo "Saved in "$FILENAME
rm -rf $TEMP_DIR # Delete temp directory

# git push
git add $FILENAME
git commit -m "ADD $FILENAME to consegne"
git push
