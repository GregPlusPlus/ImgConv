<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="fr_FR">
<context>
    <name>Core::App</name>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="38"/>
        <source>No OpenCL compatible device found !</source>
        <translation>Aucun périphérique compatible OpenCl trouvé !</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="57"/>
        <location filename="../../src/Core/App/app.cpp" line="86"/>
        <source>OCL backend error (%1)</source>
        <translation>Erreur de backend OCL(%1)</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="70"/>
        <source>File error (%1)</source>
        <translation>Erreur de fichier (%1)</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="78"/>
        <source>OCL build program error (%1)
______________________________
%2</source>
        <translation>Erreur de compilation OCL du programme (%1)
______________________________
%2</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="101"/>
        <location filename="../../src/Core/App/app.cpp" line="173"/>
        <location filename="../../src/Core/App/app.cpp" line="214"/>
        <source>Kernel already running ! Please wait.</source>
        <translation>Un noyau est déjà en cours d&apos;exécution ! Merci d&apos;attendre.</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="119"/>
        <location filename="../../src/Core/App/app.cpp" line="231"/>
        <source>
[%1] Creating program - opts. : `%2`</source>
        <translation>
[%1] Création du programme - opts. : `%2`</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="122"/>
        <location filename="../../src/Core/App/app.cpp" line="234"/>
        <source>
Chunk size : %1x%2 px.</source>
        <translation>
Taille de bloc : %1x%2 px.</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="162"/>
        <location filename="../../src/Core/App/app.cpp" line="269"/>
        <source>%1 - Running kernel ...</source>
        <translation>%1 - Exécution du noyau ...</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="224"/>
        <source>Invalid histogram.</source>
        <translation>Histogramme invalide.</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="279"/>
        <source>
%1x%2 Convolution matrix :
</source>
        <translation>
%1x%2 Matrice de convolution :
</translation>
    </message>
    <message>
        <location filename="../../src/Core/App/app.cpp" line="282"/>
        <source>Matrix is too large to be printed.</source>
        <translation>La matrice est trop grande pour être affichée.</translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::ConvKernel</name>
    <message>
        <location filename="../../src/Core/Processing/convkernel.cpp" line="25"/>
        <location filename="../../src/Core/Processing/convkernel.cpp" line="62"/>
        <location filename="../../src/Core/Processing/convkernel.cpp" line="66"/>
        <source>Source file</source>
        <translation>Fichier source</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/convkernel.cpp" line="25"/>
        <source>Open source file</source>
        <translation>Ouvrir un fichier source</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/convkernel.cpp" line="26"/>
        <source>OpenCL source (*.cl *.c);;All files (*.*)</source>
        <translation>Fichier source OpenCL (*.cl *.c);;Tous les fichiers (*.*)</translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::Custom</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/custom.cpp" line="25"/>
        <source>Kernel</source>
        <translation>Noyau</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/custom.cpp" line="25"/>
        <source>Open kernel as image file</source>
        <translation>Ouvrir une image comme noyau</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/custom.cpp" line="26"/>
        <source>CSV file (*.csv *.txt);;Image files (%1)</source>
        <translation>Fichier CSV (*.csv *.txt);;Fichiers image (%1)</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/custom.cpp" line="31"/>
        <source>Normalize kernel</source>
        <translation>Normaliser le noyay</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/custom.cpp" line="51"/>
        <source>Custom kernel</source>
        <translation>Noyau personnalisé</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/custom.cpp" line="55"/>
        <source>Allows to load a custom convolution kernel matrix from a CSV or an image file.&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Kernel : &lt;/strong&gt;The file to be loaded as a kernel.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Normalize kernel : &lt;/strong&gt;Should the kernel be normalized (sum of coefs = 1).&lt;/li&gt;&lt;/ul&gt;&lt;br&gt;When using an image as the matrix, the mapping is the following :&lt;ul&gt;&lt;li&gt;0 → -1&lt;/li&gt;&lt;li&gt;128 → 0&lt;/li&gt;&lt;li&gt;255 → +1&lt;/li&gt;&lt;/ul&gt;</source>
        <translation>Permet de charger un noyau de convolution à partir d&apos;un fichier CSV ou d&apos;une image.&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Noyau : &lt;/strong&gt;Le fichier à charger comme noyau.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Normalisation du noyau : &lt;/strong&gt;Si le noyau doit être normalisé (comme des coefs = 1).&lt;/li&gt;&lt;/ul&gt;&lt;br&gt;Lorsqu&apos;une image est utilisée, la correspondance est la suivante :&lt;ul&gt;&lt;li&gt;0 → -1&lt;/li&gt;&lt;li&gt;128 → 0&lt;/li&gt;&lt;li&gt;255 → +1&lt;/li&gt;&lt;/ul&gt;</translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::Emboss</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/emboss.cpp" line="25"/>
        <source>Size</source>
        <translation>Taille</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/emboss.cpp" line="31"/>
        <source>Smoothing</source>
        <translation>Adoucissement</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/emboss.cpp" line="55"/>
        <source>Emboss</source>
        <translation>Relief</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/emboss.cpp" line="59"/>
        <source>Applies an &lt;i&gt;Emboss&lt;/i&gt; effect.&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Size : &lt;/strong&gt;The &quot;witdh&quot; of the emboss effect along the edges. The bigger the number, the stronger the effect.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Smoothing : &lt;/strong&gt;How much the effect must be smoothed (increases the center pixel&apos;s ponderation).&lt;/li&gt;&lt;/ul&gt;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::GaussianBlur</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/gaussianblur.cpp" line="27"/>
        <source>Size</source>
        <translation>Taille</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/gaussianblur.cpp" line="33"/>
        <source>Std Dev</source>
        <translation>Std Dev</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/gaussianblur.cpp" line="57"/>
        <source>Gaussian blur</source>
        <translation>Flou gaussien</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/gaussianblur.cpp" line="61"/>
        <source>Applies a gaussian blur effect.&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Size : &lt;/strong&gt;The size of the blur effect.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Std Dev : &lt;/strong&gt;The &lt;i&gt;Standard Deviation&lt;/i&gt; of the Gaussian curve.&lt;/li&gt;&lt;/ul&gt;</source>
        <translation>Applique un effet de flou gaussien.&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Taille : &lt;/strong&gt;La taille de l&apos;effet de flou.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Std Dev : &lt;/strong&gt;La &lt;i&gt;Déviation standard&lt;/i&gt; de la Gaussienne.&lt;/li&gt;&lt;/ul&gt;</translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::MotionBlur</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/motionblur.cpp" line="25"/>
        <source>Size</source>
        <translation>Taille</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/motionblur.cpp" line="31"/>
        <source>Angle</source>
        <translation>Angle</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/motionblur.cpp" line="55"/>
        <source>Motion blur</source>
        <translation>Flou de déplacement</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/motionblur.cpp" line="59"/>
        <source>Applies a &lt;i&gt;Motion Blur&lt;/i&gt; effect.&lt;br&gt;This effect mimics a camera&apos;s shutter exposure time on moving objects.&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Size : &lt;/strong&gt;The size of the movement effect. In reality, it is determined by the shutter speed as well as the speed of the moving object.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Angle : &lt;/strong&gt;Simulates the direction of the moving object.&lt;/li&gt;&lt;/ul&gt;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::Ridge</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/ridge.cpp" line="43"/>
        <source>Ridge</source>
        <translation>Ridge</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/ridge.cpp" line="47"/>
        <source>Applies an &lt;i&gt;Ridge&lt;/i&gt; effect (a kind of edge-detection effect).&lt;br&gt;&lt;br&gt;This effect doesn&apos;t have any parameters to tweak.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::Sharpen</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/sharpen.cpp" line="25"/>
        <source>Contour strength</source>
        <translation>Intensité du contour</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/sharpen.cpp" line="31"/>
        <source>Smoothing</source>
        <translation>Adoucissement</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/sharpen.cpp" line="55"/>
        <source>Sharpen</source>
        <translation>Netteté</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/sharpen.cpp" line="59"/>
        <source>Applies a &lt;i&gt;Sharpen&lt;/i&gt; effect. This effect increases the edge&apos;s contrast.&lt;br&gt;&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Contour strength : &lt;/strong&gt;How strong the effect is. As the contrast increases, the noise does as well.&lt;/li&gt;&lt;li&gt;&lt;strong&gt;Smoothing : &lt;/strong&gt;How much the effect must be smoothed (increases the center pixel&apos;s ponderation).&lt;/li&gt;&lt;/ul&gt;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::Sobel</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/sobel.cpp" line="43"/>
        <source>Sobel</source>
        <translation>Filtre Sobel</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/sobel.cpp" line="47"/>
        <source>Applies an &lt;i&gt;Sobel&lt;/i&gt; effect (a kind of edge-detection effect).&lt;br&gt;&lt;br&gt;This effect doesn&apos;t have any parameters to tweak.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Note :&lt;/strong&gt;The convolution matrices are harcoded in &lt;i&gt;:/ocl/sobel.cl&lt;/i&gt; The matrix generated by this effect is not used by the program.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::Unity</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/unity.cpp" line="25"/>
        <source>Gain</source>
        <translation>Gain</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/unity.cpp" line="47"/>
        <source>Unity kernel</source>
        <translation>Noyau unité</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/unity.cpp" line="51"/>
        <source>Applies a Unity convolution matrix.&lt;ul&gt;&lt;li&gt;&lt;strong&gt;Gain : &lt;/strong&gt;Adjust the gain of the image.&lt;/li&gt;&lt;/ul&gt;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Core::Processing::ConvKernels::UnsharpMasking</name>
    <message>
        <location filename="../../src/Core/Processing/Kernels/unsharpmasking.cpp" line="45"/>
        <source>Unsharp masking</source>
        <translation>Masque flou</translation>
    </message>
    <message>
        <location filename="../../src/Core/Processing/Kernels/unsharpmasking.cpp" line="49"/>
        <source>Applies the &lt;i&gt;Unsharp Masking (USM)&lt;/i&gt; effect. This effect increases the edge&apos;s contrast, and is an improved version of the &lt;i&gt;Sharpen&lt;/i&gt; effect.&lt;br&gt;&lt;br&gt;This effect doesn&apos;t have any parameters to tweak.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../../src/Core/OCLWrapper/oclutils.cpp" line="41"/>
        <source>%1. Platform: %2
</source>
        <translation>%1. Plateforme : %2
</translation>
    </message>
    <message>
        <location filename="../../src/Core/OCLWrapper/oclutils.cpp" line="54"/>
        <source>  %1. Device: %2
</source>
        <translation>  %1. Périphérique : %2
</translation>
    </message>
    <message>
        <location filename="../../src/Core/OCLWrapper/oclutils.cpp" line="61"/>
        <source>    %1.1 Hardware version: %2
</source>
        <translation>    %1.1 Version matérielle : %2
</translation>
    </message>
    <message>
        <location filename="../../src/Core/OCLWrapper/oclutils.cpp" line="68"/>
        <source>    %1.2 Software version: %2
</source>
        <translation>    %1.2 Version logicielle : %2
</translation>
    </message>
    <message>
        <location filename="../../src/Core/OCLWrapper/oclutils.cpp" line="75"/>
        <source>    %1.3 OpenCL C version: %2
</source>
        <translation>    %1.3 Version de OpenCL C : %2
</translation>
    </message>
    <message>
        <location filename="../../src/Core/OCLWrapper/oclutils.cpp" line="81"/>
        <source>    %1.4 Parallel compute units: %2
</source>
        <translation>    %1.4 Unités de calcul parallèle : %2
</translation>
    </message>
</context>
<context>
    <name>UI::CodeEditorContainter</name>
    <message>
        <source>Generate code template</source>
        <translation type="vanished">Générer un modèle de code</translation>
    </message>
    <message>
        <source>Basic template</source>
        <translation type="vanished">Modèle basique</translation>
    </message>
    <message>
        <source>Convolution template</source>
        <translation type="vanished">Modèle de convolution</translation>
    </message>
    <message>
        <source>Save file</source>
        <translation type="vanished">Enregistrer le fichier</translation>
    </message>
    <message>
        <source>Save</source>
        <translation type="vanished">Enregistrer</translation>
    </message>
    <message>
        <source>Ctrl+S</source>
        <translation type="vanished">Ctrl+S</translation>
    </message>
    <message>
        <source>Save as</source>
        <translation type="vanished">Enregistrer sous</translation>
    </message>
    <message>
        <source>Ctrl+Shift+S</source>
        <translation type="vanished">Ctrl+Shift+S</translation>
    </message>
    <message>
        <source>Apply</source>
        <translation type="vanished">Appliquer</translation>
    </message>
    <message>
        <source>F9</source>
        <translation type="vanished">F9</translation>
    </message>
    <message>
        <source>Open file</source>
        <translation type="vanished">Ouvrir un fichier</translation>
    </message>
    <message>
        <source>Ctrl+Shift+O</source>
        <translation type="vanished">Ctrl+Shift+O</translation>
    </message>
    <message>
        <source>Undo</source>
        <translation type="vanished">Défaire</translation>
    </message>
    <message>
        <source>Redo</source>
        <translation type="vanished">Refaire</translation>
    </message>
    <message>
        <source>Untitled</source>
        <translation type="vanished">Sans-nom</translation>
    </message>
    <message>
        <source>File is saved</source>
        <translation type="vanished">Le fichier est enregistré</translation>
    </message>
    <message>
        <source>File is not saved</source>
        <translation type="vanished">Le fichier n&apos;est pas enregistré</translation>
    </message>
    <message>
        <source>Open OpenCL source file</source>
        <translation type="vanished">Ouvrir un fichier source OpenCL</translation>
    </message>
    <message>
        <source>OpenCL source (*.cl *.c);;All files (*.*)</source>
        <translation type="vanished">Source OpenCL (*.cl *.c);;Tous les fichiers (*.*)</translation>
    </message>
    <message>
        <source>Save OpenCL source file</source>
        <translation type="vanished">Enregistrer le fichier source OpenCL</translation>
    </message>
    <message>
        <source>Save OpenCL source file as...</source>
        <translation type="vanished">Enregistrer le fichier source OpenCL sous ...</translation>
    </message>
    <message>
        <source>Unsaved file</source>
        <translation type="vanished">Fichier non enregistré</translation>
    </message>
    <message>
        <source>Save file before proceeding ?</source>
        <translation type="vanished">Enregistrer avant de continuer ?</translation>
    </message>
</context>
<context>
    <name>UI::Components::ButtonColorPicker</name>
    <message>
        <source>Pick color</source>
        <translation type="vanished">Sélectionner une couleur</translation>
    </message>
</context>
<context>
    <name>UI::Components::HistogramWidget</name>
    <message>
        <source>X : %1 R : %2 G : %3 B : %4</source>
        <translation type="vanished">X : %1 R : %2 G : %3 B : %4</translation>
    </message>
    <message>
        <source>No Data</source>
        <translation type="vanished">Pas de données</translation>
    </message>
</context>
<context>
    <name>UI::Dialogs::CreateImageDialog</name>
    <message>
        <source>Create image</source>
        <translation type="vanished">Créer une image</translation>
    </message>
    <message>
        <source>Width :</source>
        <translation type="vanished">Largeur :</translation>
    </message>
    <message>
        <source>Height :</source>
        <translation type="vanished">Hauteur :</translation>
    </message>
    <message>
        <source>Fill color :</source>
        <translation type="vanished">Couleur de remplissage :</translation>
    </message>
</context>
<context>
    <name>UI::Dialogs::ProcessOptionsDialog</name>
    <message>
        <source>Process options</source>
        <translation type="vanished">Options de traitement</translation>
    </message>
    <message>
        <source>Chunk size factor</source>
        <translation type="vanished">Taille du facteur de bloc</translation>
    </message>
</context>
<context>
    <name>UI::Dialogs::SelectDeviceDialog</name>
    <message>
        <source>Select device</source>
        <translation type="vanished">Sélectionner un périphérique</translation>
    </message>
    <message>
        <source>Device :</source>
        <translation type="vanished">Périphérique :</translation>
    </message>
</context>
<context>
    <name>UI::Dialogs::WaitDialog</name>
    <message>
        <source>Work in progress</source>
        <translation type="vanished">Travail en cours</translation>
    </message>
    <message>
        <source>Cancel process</source>
        <translation type="vanished">Abandonner le processus</translation>
    </message>
    <message>
        <source>Canceling process...</source>
        <translation type="vanished">Abandon du processus...</translation>
    </message>
</context>
<context>
    <name>UI::FileNamePicker</name>
    <message>
        <source>...</source>
        <translation type="vanished">...</translation>
    </message>
</context>
<context>
    <name>UI::GUI::CodeEditorContainter</name>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="39"/>
        <source>Generate code template</source>
        <translation>Générer un modèle de code</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="41"/>
        <source>Basic template</source>
        <translation>Modèle basique</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="44"/>
        <source>Convolution template</source>
        <translation>Modèle de convolution</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="51"/>
        <source>Save file</source>
        <translation>Enregistrer le fichier</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="53"/>
        <source>Save</source>
        <translation>Enregistrer</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="53"/>
        <source>Ctrl+S</source>
        <translation>Ctrl+S</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="54"/>
        <source>Save as</source>
        <translation>Enregistrer sous</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="54"/>
        <source>Ctrl+Shift+S</source>
        <translation>Ctrl+Shift+S</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="57"/>
        <source>Apply</source>
        <translation>Appliquer</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="57"/>
        <source>F9</source>
        <translation>F9</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="59"/>
        <source>Open file</source>
        <translation>Ouvrir un fichier</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="59"/>
        <source>Ctrl+Shift+O</source>
        <translation>Ctrl+Shift+O</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="62"/>
        <source>Undo</source>
        <translation>Défaire</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="63"/>
        <source>Redo</source>
        <translation>Refaire</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="71"/>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="95"/>
        <source>Untitled</source>
        <translation>Sans-nom</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="107"/>
        <source>File is saved</source>
        <translation>Le fichier est enregistré</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="110"/>
        <source>File is not saved</source>
        <translation>Le fichier n&apos;est pas enregistré</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="134"/>
        <source>Open OpenCL source file</source>
        <translation>Ouvrir un fichier source OpenCL</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="135"/>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="165"/>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="195"/>
        <source>OpenCL source (*.cl *.c);;All files (*.*)</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="164"/>
        <source>Save OpenCL source file</source>
        <translation>Enregistrer le fichier source OpenCL</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="194"/>
        <source>Save OpenCL source file as...</source>
        <translation>Enregistrer le fichier source OpenCL sous ...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="227"/>
        <source>Unsaved file</source>
        <translation>Fichier non enregistré</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/CodeEditor/codeeditorcontainer.cpp" line="227"/>
        <source>Save file before proceeding ?</source>
        <translation>Enregistrer avant de continuer ?</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Components::ButtonColorPicker</name>
    <message>
        <location filename="../../src/UI/GUI/Components/ButtonColorPicker/buttoncolorpicker.cpp" line="25"/>
        <source>Pick color</source>
        <translation>Sélectionner une couleur</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Components::HistogramWidget</name>
    <message>
        <location filename="../../src/UI/GUI/Components/HistogramWidget/histogramwidget.cpp" line="86"/>
        <source>X : %1 R : %2 G : %3 B : %4</source>
        <translation>X : %1 R : %2 G : %3 B : %4</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Components/HistogramWidget/histogramwidget.cpp" line="109"/>
        <source>No Data</source>
        <translation>Pas de données</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Dialogs::CreateImageDialog</name>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/CreateImageDialog/createimagedialog.cpp" line="27"/>
        <source>Create image</source>
        <translation>Créer une image</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/CreateImageDialog/createimagedialog.cpp" line="46"/>
        <source>Width :</source>
        <translation>Largeur :</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/CreateImageDialog/createimagedialog.cpp" line="47"/>
        <source>Height :</source>
        <translation>Hauteur :</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/CreateImageDialog/createimagedialog.cpp" line="48"/>
        <source>Fill color :</source>
        <translation>Couleur de remplissage :</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Dialogs::ProcessOptionsDialog</name>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/ProcessOptionsDialog/processoptionsdialog.cpp" line="28"/>
        <source>Process options</source>
        <translation>Options de traitement</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/ProcessOptionsDialog/processoptionsdialog.cpp" line="47"/>
        <source>Chunk size factor</source>
        <translation>Taille du facteur de bloc</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Dialogs::SelectDeviceDialog</name>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/SelectDeviceDialog/selectdevicedialog.cpp" line="27"/>
        <source>Select device</source>
        <translation>Sélectionner un périphérique</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/SelectDeviceDialog/selectdevicedialog.cpp" line="37"/>
        <source>Device :</source>
        <translation>Périphérique :</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Dialogs::WaitDialog</name>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/WaitDialog/waitdialog.cpp" line="29"/>
        <source>Work in progress</source>
        <translation>Travail en cours</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/WaitDialog/waitdialog.cpp" line="47"/>
        <source>Cancel process</source>
        <translation>Abandonner le processus</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Dialogs/WaitDialog/waitdialog.cpp" line="96"/>
        <source>Canceling process...</source>
        <translation>Abandon du processus...</translation>
    </message>
</context>
<context>
    <name>UI::GUI::FileNamePicker</name>
    <message>
        <location filename="../../src/UI/GUI/FilterSettingsWidget/filenamepicker.cpp" line="33"/>
        <source>...</source>
        <translation>...</translation>
    </message>
</context>
<context>
    <name>UI::GUI::ImageViewerContainer</name>
    <message>
        <location filename="../../src/UI/GUI/ImageViewer/imageviewercontainer.cpp" line="35"/>
        <source>Fit image</source>
        <translation>Ajuster l&apos;image</translation>
    </message>
</context>
<context>
    <name>UI::GUI::MainWindow</name>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="48"/>
        <source>Kernel canceled</source>
        <translation>Noyau abandonné</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="52"/>
        <source>Critical error</source>
        <translation>Erreur critique</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="57"/>
        <source>OpenCL error</source>
        <translation>Erreur OpenCL</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="57"/>
        <source>OpenCL backend error</source>
        <translation>Erreur de backend OpenCL</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="98"/>
        <source>%1 - Processing done in %2 ms. Approx %3 px/sec.</source>
        <translation>%1 - Traitement effectué en %2 ms. Environ %3 px/sec.</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="112"/>
        <source>%1x%2 (%3 bytes)</source>
        <translation>%1x%2 (%3 octets)</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="144"/>
        <source>Processing image...</source>
        <translation>Traitement de l&apos;image...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="164"/>
        <source>Computing histogram...</source>
        <translation>Calcul de l&apos;histogramme...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="179"/>
        <source>Correcting image...</source>
        <translation>Correction de l&apos;image...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="188"/>
        <source>Open image file</source>
        <translation>Ouvrir unfichier image</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="189"/>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="246"/>
        <source>Image files (*.png *.jpg *.jpeg *.bmp *.gif)</source>
        <translation>Fichiers image (*.png *.jpg *.jpeg *.bmp *.gif)</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="195"/>
        <source>Opening image...</source>
        <translation>Ouverture de l&apos;image...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="199"/>
        <source>Image loaded in %1 ms.</source>
        <translation>Image chargée en %1 ms.</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="200"/>
        <source>[%1] Image loaded in %2 ms.</source>
        <translation>[%1] Image chargée en %2 ms.</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="235"/>
        <source>Created image of size %1x%2.</source>
        <translation>Image de taille %1x%2 créée.</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="245"/>
        <source>Save image file</source>
        <translation>Enregistrer le fichier image</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="252"/>
        <source>Exporting image...</source>
        <translation>Export de l&apos;image...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="256"/>
        <source>[%1] Image saved in %2 ms.</source>
        <translation>[%1] Image enregistrée en %2 ms.</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="291"/>
        <source>About this program</source>
        <translation>A propos de ce programme</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="292"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt; [Rev. %2]&lt;br&gt;&lt;br&gt;Some icons are provided under a &lt;a href=&apos;https://creativecommons.org/licenses/by/3.0/&apos;&gt;Creative Commons Attribution 3.0 License&lt;/a&gt; by Yusuke Kamiyamane &lt;a href=&apos;https://p.yusukekamiyamane.com/&apos;&gt;(Fugue Icons)&lt;/a&gt;.&lt;br&gt;&lt;br&gt;%3&lt;hr&gt;%4</source>
        <translation>&lt;h1&gt;%1&lt;/h1&gt; [Rev. %2]&lt;br&gt;&lt;br&gt;Certaines icônes sont fournies sous license &lt;a href=&apos;https://creativecommons.org/licenses/by/3.0/&apos;&gt;Creative Commons Attribution 3.0 License&lt;/a&gt; par Yusuke Kamiyamane &lt;a href=&apos;https://p.yusukekamiyamane.com/&apos;&gt;(Fugue Icons)&lt;/a&gt;.&lt;br&gt;&lt;br&gt;%3&lt;hr&gt;%4</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="316"/>
        <source>Unsaved file</source>
        <translation>Fichier non enregistré</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="316"/>
        <source>Save processed image before closing ?</source>
        <translation>Enregistrer l&apos;image traitée avant de continuer ?</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="338"/>
        <source>&amp;File</source>
        <translation>&amp;Fichier</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="340"/>
        <source>&amp;Open</source>
        <translation>&amp;Ouvrir</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="340"/>
        <source>Ctrl+O</source>
        <translation>Ctrl+O</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="341"/>
        <source>&amp;Create image</source>
        <translation>&amp;Créer une image</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="341"/>
        <source>Ctrl+N</source>
        <translation>Ctrl+N</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="342"/>
        <source>&amp;Export processed image</source>
        <translation>&amp;Exporter l&apos;image traitée</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="342"/>
        <source>Ctrl+E</source>
        <translation>Ctrl+E</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="344"/>
        <source>Select &amp;device</source>
        <translation>Sélectionner le &amp;périphérique</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="354"/>
        <source>&amp;Exit</source>
        <translation>&amp;Quitter</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="354"/>
        <source>Ctrl+W</source>
        <translation>Ctrl+W</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="356"/>
        <source>&amp;Process</source>
        <translation>&amp;Traitement</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="357"/>
        <source>Process &amp;options</source>
        <translation>&amp;Options de traitement</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="359"/>
        <source>Reload current &amp;kernel</source>
        <translation>&amp;Recharger le noyau courant</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="359"/>
        <source>F5</source>
        <translation>F5</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="362"/>
        <source>&amp;Run</source>
        <translation>&amp;Exécuter</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="362"/>
        <source>Ctrl+R</source>
        <translation>Ctrl+R</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="363"/>
        <source>&amp;Backfeed</source>
        <translation>Rétro-&amp;alimenter</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="363"/>
        <source>Ctrl+B</source>
        <translation>Ctrl+B</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="369"/>
        <source>&amp;Help</source>
        <translation>&amp;Aide</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="370"/>
        <source>&amp;About this program</source>
        <translation>&amp;A propos de ce programme</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="371"/>
        <source>About &amp;Qt</source>
        <translation>A propos de &amp;Qt</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="375"/>
        <source>Open&amp;CL Devices</source>
        <translation>Périphériques Open&amp;CL</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="376"/>
        <source>OpenCL Devices</source>
        <translation>Périphériques OpenCL</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="379"/>
        <source>Tools</source>
        <translation>Outils</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="384"/>
        <source>Filter : </source>
        <translation>Filtre : </translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="404"/>
        <source>Selected device : %1</source>
        <translation>Périphérique sélectionné : %1</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="440"/>
        <source>Original image</source>
        <translation>Image originale</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="441"/>
        <source>Processed image</source>
        <translation>Image traitée</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="450"/>
        <source>Original</source>
        <translation>Image originale</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="451"/>
        <source>Processed</source>
        <translation>Image traitée</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/MainWindow/mainwindow.cpp" line="452"/>
        <source>Code editor</source>
        <translation>Editeur de code</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Panels::FilterSettingsDock</name>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="24"/>
        <source>Filter settings</source>
        <translation>Paramètres du filtre</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="39"/>
        <source>Reset settings</source>
        <translation>Réinitialiser les paramètres</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="42"/>
        <source>Export matrix</source>
        <translation>Exporter la matrice</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="51"/>
        <source>&lt;h2&gt;Filter description&lt;/h2&gt;</source>
        <translation>&lt;h2&gt;Description du filtre&lt;/h2&gt;</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="86"/>
        <source>&lt;h2&gt;%1&lt;/h2&gt;&lt;hr&gt;%2</source>
        <translation>&lt;h2&gt;%1&lt;/h2&gt;&lt;hr&gt;%2</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="100"/>
        <source>Save Convolution matrix...</source>
        <translation>Enregistrer la matrice de convolution...</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp" line="101"/>
        <source>CSV File (*.csv);;All files (*.*)</source>
        <translation>Fichier CSV (*.csv);;Tous les fichiers (*.*)</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Panels::ImageCorrectionPanel</name>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="26"/>
        <source>Image correction</source>
        <translation>Correction de l&apos;image</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="32"/>
        <source>Histogram</source>
        <translation>Histogramme</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="36"/>
        <source>CDF</source>
        <translation>DFC</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="37"/>
        <source>Cumulative Distribution Frequency</source>
        <translation>Distribution Fréquenctielle Cumulée</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="41"/>
        <source>Original image histogram</source>
        <translation>Histogramme de l&apos;image originale</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="42"/>
        <source>Processed image histogram</source>
        <translation>Histogramme de l&apos;image traitée</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="43"/>
        <source>Original image CDF</source>
        <translation>DFC de l&apos;image originale</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="44"/>
        <source>Processed image CDF</source>
        <translation>DFC de l&apos;image traitée</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="46"/>
        <source>Convert to grayscale</source>
        <translation>Convertir en nuances de gris</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="50"/>
        <source>Invert colors</source>
        <translation>Inverser les couleurs</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp" line="54"/>
        <source>Histogram equalization</source>
        <translation>Egalisation de l&apos;histogramme</translation>
    </message>
</context>
<context>
    <name>UI::GUI::Panels::LogPanel</name>
    <message>
        <location filename="../../src/UI/GUI/Panels/LogPanel/logpanel.cpp" line="24"/>
        <source>Logs</source>
        <translation>Logs</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/LogPanel/logpanel.cpp" line="37"/>
        <source>Info</source>
        <translation>Infos</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/LogPanel/logpanel.cpp" line="38"/>
        <source>Output</source>
        <translation>Sortie</translation>
    </message>
    <message>
        <location filename="../../src/UI/GUI/Panels/LogPanel/logpanel.cpp" line="39"/>
        <source>Errors</source>
        <translation>Erreurs</translation>
    </message>
</context>
<context>
    <name>UI::ImageViewerContainer</name>
    <message>
        <source>Fit image</source>
        <translation type="vanished">Ajuster l&apos;image</translation>
    </message>
</context>
<context>
    <name>UI::MainWindow</name>
    <message>
        <source>Kernel canceled</source>
        <translation type="vanished">Noyau abandonné</translation>
    </message>
    <message>
        <source>Critical error</source>
        <translation type="vanished">Erreur critique</translation>
    </message>
    <message>
        <source>OpenCL error</source>
        <translation type="vanished">Erreur OpenCL</translation>
    </message>
    <message>
        <source>OpenCL backend error</source>
        <translation type="vanished">Erreur de backend OpenCL</translation>
    </message>
    <message>
        <source>%1 - Processing done in %2 ms. Approx %3 px/sec.</source>
        <translation type="vanished">%1 - Traitement effectué en %2 ms. Environ %3 px/sec.</translation>
    </message>
    <message>
        <source>%1x%2 (%3 bytes)</source>
        <translation type="vanished">%1x%2 (%3 octets)</translation>
    </message>
    <message>
        <source>Processing image...</source>
        <translation type="vanished">Traitement de l&apos;image...</translation>
    </message>
    <message>
        <source>Computing histogram...</source>
        <translation type="vanished">Calcul de l&apos;histogramme...</translation>
    </message>
    <message>
        <source>Correcting image...</source>
        <translation type="vanished">Correction de l&apos;image...</translation>
    </message>
    <message>
        <source>Open image file</source>
        <translation type="vanished">Ouvrir unfichier image</translation>
    </message>
    <message>
        <source>Image files (*.png *.jpg *.jpeg *.bmp *.gif)</source>
        <translation type="vanished">Fichiers image (*.png *.jpg *.jpeg *.bmp *.gif)</translation>
    </message>
    <message>
        <source>Opening image...</source>
        <translation type="vanished">Ouverture de l&apos;image...</translation>
    </message>
    <message>
        <source>Image loaded in %1 ms.</source>
        <translation type="vanished">Image chargée en %1 ms.</translation>
    </message>
    <message>
        <source>[%1] Image loaded in %2 ms.</source>
        <translation type="vanished">[%1] Image chargée en %2 ms.</translation>
    </message>
    <message>
        <source>Created image of size %1x%2.</source>
        <translation type="vanished">Image de taille %1x%2 créée.</translation>
    </message>
    <message>
        <source>Save image file</source>
        <translation type="vanished">Enregistrer le fichier image</translation>
    </message>
    <message>
        <source>Exporting image...</source>
        <translation type="vanished">Export de l&apos;image...</translation>
    </message>
    <message>
        <source>[%1] Image saved in %2 ms.</source>
        <translation type="vanished">[%1] Image enregistrée en %2 ms.</translation>
    </message>
    <message>
        <source>About this program</source>
        <translation type="vanished">A propos de ce programme</translation>
    </message>
    <message>
        <source>&lt;h1&gt;%1&lt;/h1&gt; [Rev. %2]&lt;br&gt;&lt;br&gt;Some icons are provided under a &lt;a href=&apos;https://creativecommons.org/licenses/by/3.0/&apos;&gt;Creative Commons Attribution 3.0 License&lt;/a&gt; by Yusuke Kamiyamane &lt;a href=&apos;https://p.yusukekamiyamane.com/&apos;&gt;(Fugue Icons)&lt;/a&gt;.&lt;br&gt;&lt;br&gt;%3&lt;hr&gt;%4</source>
        <translation type="vanished">&lt;h1&gt;%1&lt;/h1&gt; [Rev. %2]&lt;br&gt;&lt;br&gt;Certaines icônes sont fournies sous license &lt;a href=&apos;https://creativecommons.org/licenses/by/3.0/&apos;&gt;Creative Commons Attribution 3.0 License&lt;/a&gt; par Yusuke Kamiyamane &lt;a href=&apos;https://p.yusukekamiyamane.com/&apos;&gt;(Fugue Icons)&lt;/a&gt;.&lt;br&gt;&lt;br&gt;%3&lt;hr&gt;%4</translation>
    </message>
    <message>
        <source>Unsaved file</source>
        <translation type="vanished">Fichier non enregistré</translation>
    </message>
    <message>
        <source>Save processed image before closing ?</source>
        <translation type="vanished">Enregistrer l&apos;image traitée avant de continuer ?</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation type="vanished">&amp;Fichier</translation>
    </message>
    <message>
        <source>&amp;Open</source>
        <translation type="vanished">&amp;Ouvrir</translation>
    </message>
    <message>
        <source>Ctrl+O</source>
        <translation type="vanished">Ctrl+O</translation>
    </message>
    <message>
        <source>&amp;Create image</source>
        <translation type="vanished">&amp;Créer une image</translation>
    </message>
    <message>
        <source>Ctrl+N</source>
        <translation type="vanished">Ctrl+N</translation>
    </message>
    <message>
        <source>Export processed image</source>
        <translation type="vanished">Exporter l&apos;image traitée</translation>
    </message>
    <message>
        <source>Ctrl+E</source>
        <translation type="vanished">Ctrl+E</translation>
    </message>
    <message>
        <source>&amp;Export processed image</source>
        <translation type="vanished">&amp;Exporter l&apos;image traitée</translation>
    </message>
    <message>
        <source>Select &amp;device</source>
        <translation type="vanished">Sélectionner le &amp;périphérique</translation>
    </message>
    <message>
        <source>&amp;Exit</source>
        <translation type="vanished">&amp;Quitter</translation>
    </message>
    <message>
        <source>Ctrl+W</source>
        <translation type="vanished">Ctrl+W</translation>
    </message>
    <message>
        <source>&amp;Process</source>
        <translation type="vanished">&amp;Traitement</translation>
    </message>
    <message>
        <source>Process &amp;options</source>
        <translation type="vanished">&amp;Options de traitement</translation>
    </message>
    <message>
        <source>Reload current &amp;kernel</source>
        <translation type="vanished">&amp;Recharger le noyau courant</translation>
    </message>
    <message>
        <source>F5</source>
        <translation type="vanished">F5</translation>
    </message>
    <message>
        <source>&amp;Run</source>
        <translation type="vanished">&amp;Exécuter</translation>
    </message>
    <message>
        <source>Ctrl+R</source>
        <translation type="vanished">Ctrl+R</translation>
    </message>
    <message>
        <source>&amp;Backfeed</source>
        <translation type="vanished">Rétro-&amp;alimenter</translation>
    </message>
    <message>
        <source>Ctrl+B</source>
        <translation type="vanished">Ctrl+B</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation type="vanished">&amp;Aide</translation>
    </message>
    <message>
        <source>&amp;About this program</source>
        <translation type="vanished">&amp;A propos de ce programme</translation>
    </message>
    <message>
        <source>About &amp;Qt</source>
        <translation type="vanished">A propos de &amp;Qt</translation>
    </message>
    <message>
        <source>Open&amp;CL Devices</source>
        <translation type="vanished">Périphériques Open&amp;CL</translation>
    </message>
    <message>
        <source>OpenCL Devices</source>
        <translation type="vanished">Périphériques OpenCL</translation>
    </message>
    <message>
        <source>Tools</source>
        <translation type="vanished">Outils</translation>
    </message>
    <message>
        <source>Filter : </source>
        <translation type="vanished">Filtre : </translation>
    </message>
    <message>
        <source>Selected device : %1</source>
        <translation type="vanished">Périphérique sélectionné : %1</translation>
    </message>
    <message>
        <source>Original image</source>
        <translation type="vanished">Image originale</translation>
    </message>
    <message>
        <source>Processed image</source>
        <translation type="vanished">Image traitée</translation>
    </message>
    <message>
        <source>Original</source>
        <translation type="vanished">Image originale</translation>
    </message>
    <message>
        <source>Processed</source>
        <translation type="vanished">Image traitée</translation>
    </message>
    <message>
        <source>Code editor</source>
        <translation type="vanished">Editeur de code</translation>
    </message>
</context>
<context>
    <name>UI::Panels::FilterSettingsDock</name>
    <message>
        <source>Filter settings</source>
        <translation type="vanished">Paramètres du filtre</translation>
    </message>
    <message>
        <source>Reset settings</source>
        <translation type="vanished">Réinitialiser les paramètres</translation>
    </message>
    <message>
        <source>Export matrix</source>
        <translation type="vanished">Exporter la matrice</translation>
    </message>
    <message>
        <source>&lt;h2&gt;Filter description&lt;/h2&gt;</source>
        <translation type="vanished">&lt;h2&gt;Description du filtre&lt;/h2&gt;</translation>
    </message>
    <message>
        <source>&lt;h2&gt;%1&lt;/h2&gt;&lt;hr&gt;%2</source>
        <translation type="vanished">&lt;h2&gt;%1&lt;/h2&gt;&lt;hr&gt;%2</translation>
    </message>
    <message>
        <source>Save Convolution matrix...</source>
        <translation type="vanished">Enregistrer la matrice de convolution...</translation>
    </message>
    <message>
        <source>CSV File (*.csv);;All files (*.*)</source>
        <translation type="vanished">Fichier CSV (*.csv);;Tous les fichiers (*.*)</translation>
    </message>
</context>
<context>
    <name>UI::Panels::ImageCorrectionPanel</name>
    <message>
        <source>Image correction</source>
        <translation type="vanished">Correction de l&apos;image</translation>
    </message>
    <message>
        <source>Histogram</source>
        <translation type="vanished">Histogramme</translation>
    </message>
    <message>
        <source>CDF</source>
        <translation type="vanished">DFC</translation>
    </message>
    <message>
        <source>Cumulative Distribution Frequency</source>
        <translation type="vanished">Distribution Fréquenctielle Cumulée</translation>
    </message>
    <message>
        <source>Original image histogram</source>
        <translation type="vanished">Histogramme de l&apos;image originale</translation>
    </message>
    <message>
        <source>Processed image histogram</source>
        <translation type="vanished">Histogramme de l&apos;image traitée</translation>
    </message>
    <message>
        <source>Original image CDF</source>
        <translation type="vanished">DFC de l&apos;image originale</translation>
    </message>
    <message>
        <source>Processed image CDF</source>
        <translation type="vanished">DFC de l&apos;image traitée</translation>
    </message>
    <message>
        <source>Convert to grayscale</source>
        <translation type="vanished">Convertir en nuances de gris</translation>
    </message>
    <message>
        <source>Invert colors</source>
        <translation type="vanished">Inverser les couleurs</translation>
    </message>
    <message>
        <source>Histogram equalization</source>
        <translation type="vanished">Egalisation de l&apos;histogramme</translation>
    </message>
</context>
<context>
    <name>UI::Panels::LogPanel</name>
    <message>
        <source>Logs</source>
        <translation type="vanished">Logs</translation>
    </message>
    <message>
        <source>Info</source>
        <translation type="vanished">Infos</translation>
    </message>
    <message>
        <source>Output</source>
        <translation type="vanished">Sortie</translation>
    </message>
    <message>
        <source>Errors</source>
        <translation type="vanished">Erreurs</translation>
    </message>
</context>
</TS>
