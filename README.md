# pyJacChemistryModel
This chemistryModel can be used in the latest OpenFOAM-dev (today is 4th July 2018).
## Prerequisites
### install [pyJac](https://github.com/SLACKHA/pyJac) .
### use pyJac to generate analytical Jacobians code with the language of `c` for giving chemical mechanism.
```python -m pyjac --lang c --last_species N2 --input grimech30.dat --thermo thermo30.dat --build_path ./out```
### generate shared library
```python -m pyjac.libgen --source_dir ./out --lang c -out $FOAM_USER_LIBBIN```

## compile
### add this to `options` in the `chemistryModel` of OpenFOAM
```
-I$(path_to_where_you_generate_the_code)/pyJac/out \
-I$(path_to_where_you_generate_the_code)/pyJac/out/jacobs \
-L$(FOAM_USER_LIBBIN) \    
-lc_pyjac  
```
### revise `BasicChemistryModels.C`
```#include "CCMChemistryModel.H"```
`makeChemistryModelType` using `pyJacChemistryModel`
### revise `makeChemistrySolverTypes.H`
```
                                                                                \
    typedef SS<pyJacChemistryModel<Comp, Thermo>> pyJac##SS##Comp##Thermo;      \
                                                                                \
    defineTemplateTypeNameAndDebugWithName                                      \
    (                                                                           \
        pyJac##SS##Comp##Thermo,                                                \
        (#SS"<" + word(pyJacChemistryModel<Comp, Thermo>::typeName_()) + "<"    \
        + word(Comp::typeName_()) + "," + Thermo::typeName() + ">>").c_str(),   \
        0                                                                       \
    );                                                                          \
                                                                                \
    BasicChemistryModel<Comp>::                                                 \
        add##thermo##ConstructorToTable<pyJac##SS##Comp##Thermo>                \
        add##pyJac##SS##Comp##Thermo##thermo##ConstructorTo##BasicChemistryModel\
##Comp##Table_; 
```
## Using
`pyJacChemistryModel` is a depreived class of standardChemistryModel. We can choose it in the case through setting `method` to pyJac in `chemistryType` in `chemistryProperties`.
When we change the chemical mechanism, we just need to generate the shared library and put it in the same place.
