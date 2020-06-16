currentDir=$(ls new201*.root)
for file in $currentDir
do
  mv $file ${file:3}
done
