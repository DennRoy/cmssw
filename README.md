# How to make NanoAOD samples from embedded Z -> tautau MiniAOD

This setup allows to make NanoAODv4 samples from the embedded MiniAOD samples. For more infomation on the embedded samples, see:

    https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauTauEmbeddingSamples2016
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauTauEmbeddingSamples2017
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauTauEmbeddingSamples2018

First set up a repository:

    export SCRAM_ARCH=slc7_amd64_gcc700
    cmsrel CMSSW_10_4_0
    cd CMSSW_10_4_0/src/
    cmsenv
    git cms-init
    git cms-merge-topic DennRoy:NanoEmbedding2017_CMSSW1040

I used CMSSW_10_4_0 for this. It may also work with a 10_2_X setup. If you want to use your own setup, just make sure to apply all changes from these two commits:

    https://github.com/DennRoy/cmssw/commit/f247ec0b57294191ff1e44d8903fb4f96e2cd8a6
    https://github.com/DennRoy/cmssw/commit/76d41cbc2a315ad9412e5d2448480f2fda112e4b

Next, here is a template configuration to be used with `cmsRun`:

    https://github.com/DennRoy/cmssw/blob/NanoEmbedding2017_CMSSW1040/TEMPLATE_Embed_NANO.py

The commented section in the beginning of that file contains instructions on the 5 placeholders in the config that need to be replaced. Once this is done, simply run `cmsRun` with the python configuration as argument.


NOTE: In the template I wrote to use `eras.Run2_2017,eras.run2_nanoAOD_94XMiniAODv2` for the condition when processing 2017 files. It turns out that the MiniAOD files were actually made with "94XMiniAODv1". However, a short test has shown that using "v1" instead of "v2" (or vice versa) only affects the three variables `Tau_rawMVAoldDM2017v1`, `Tau_rawMVAoldDM` and `Tau_idMVAoldDM2017v1`, which are all obsolete variables anyway.
