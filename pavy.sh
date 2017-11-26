#! /bin/sh
echo "Using patch url:" $1
# user=$(echo $1 | sed -n 's/https:\/\/enzienaudio\.com\/h\/\(\w*\)\/.*/\1/p')
patchname=$(echo $1 | sed -n 's/https:\/\/enzienaudio\.com\/h\/\w*\/\(\w*\)\/.*/\1/p')
# version=$(echo $1 | sed -n 's/https:\/\/enzienaudio\.com\/h\/\w*\/\w*\/\([0-9]*\)\/.*/\1/p')

# echo $user
echo "Patchname:" $patchname
# echo $version
rm $patchname.c.zip heavy/* main

echo "Downloading and extracting patch sources..."
wget -q $1


sed -i "s/#include \"heavy\/Heavy_\(\w*\)\.h\".*/#include \"heavy\/Heavy_$patchname.h\"/" main.c
sed -i "s/.*\(HeavyContextInterface\).*/    HeavyContextInterface *context = hv_$patchname\_new(sampleRate);/" main.c

unzip -o $patchname.c.zip -d heavy/

echo "Compiling"
g++ -std=gnu++11 heavy/*.cpp heavy/*.c main.c -D_REENTRANT -lpulse-simple -lpulse -lm -o main

echo "Done. Running patch."
./main
