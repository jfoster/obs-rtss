# obs-rtss

An obs-studio & RTSS plugin

## Installation

### Prerequisites
* Windows 8.1 or 10
* [obs-studio](https://obsproject.com/) 26.1+
* [Rivatuner Statistics Server](https://www.guru3d.com/files-details/rtss-rivatuner-statistics-server-download.html)
* [A way to unextract .zip files](https://www.7-zip.org)

### Instructions
1. Download a [precompiled binary release](https://github.com/jfoster/obs-rtss/releases)
2. Unextract the .zip file
3. Merge the obs-studio folder with your obs-studio installation, usually located at ```C:\Program Files\obs-studio\```

## Building

### Prerequisites
* My forked obs-studio 26.1+ dev environment.
* [All prerequisites for building obs-studio](https://obsproject.com/wiki/Install-Instructions#windows-build-directions)

### Instructions
1. Obtain my forked obs-studio dev enviroment using git ```git clone --recursive https://github.com/jfoster/obs-studio```
2. Change to the obs-studio directory ```cd obs-studio```
3. Checkout the 26.1 branch ```git checkout 26.1.0-obs-rtss```
4. Download submodules ```git submodule update --init --recursive```
5. [Configure and build obs-studio](https://obsproject.com/wiki/Install-Instructions#windows-build-directions)
