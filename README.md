# pyJacChemistryModel
This chemistryModel can be used in the latest OpenFOAM-dev (today is 4th July 2018). Besides, OF-6 is OK.

## Prerequisites
### install [optionLoop](https://github.com/SLACKHA/optionLoop).
### install [pyJac](https://github.com/SLACKHA/pyJac).
### generate analytical Jacobians code
under the environment of OpenFOAM-6:

```
cd $WM_PROJECT_USER_DIR
mkdir pyJac
cp $FOAM_TUTORIALS/combustion/reactingFoam/RAS/SandiaD_LTS/chemkin/grimech30.dat pyJac
cp $FOAM_TUTORIALS/combustion/reactingFoam/RAS/SandiaD_LTS/chemkin/thermo30.dat pyJac
cd pyJac
python -m pyjac --lang c --last_species N2 --input grimech30.dat --thermo thermo30.dat --build_path ./out
```

### generate shared library
still in the ``pyJac`` directory:
```
python -m pyjac.libgen --source_dir ./out --lang c -out $FOAM_USER_LIBBIN
```

## ``wmake`` this pyJacChemistryModel lib

## Using
```
mkdir $FOAM_RUN
run
cp -r $FOAM_TUTORIALS/combustion/reactingFoam/RAS/SandiaD_LTS ./
cd SandiaD_LTS
foamDictionary -entry chemistryType.method -set pyJac constant/chemistryProperties
sed -i '$a\libs ("libpyJacChemistryModel.so" );' system/controlDict
foamCleanTutorials
./Allrun
```