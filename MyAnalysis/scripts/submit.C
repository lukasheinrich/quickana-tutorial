void submit (std::string submitDir)
{
  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;

  // scan for datasets in the given directory
  // this works if you are on lxplus, otherwise you'd want to copy over files
  // to your local machine and use a local path.  if you do so, make sure
  // that you copy all subdirectories and point this to the directory
  // containing all the files, not the subdirectories.

  // use SampleHandler to scan a directory for particular MC single file:
  SH::ScanDir().sampleDepth(0).samplePattern("*pool.root*").scan(sh, "/input");

  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  sh.setMetaString ("nc_tree", "CollectionTree");

  // further sample handler configuration may go here

  // print out the samples we found
  sh.print ();

  // this is the basic description of our job
  EL::Job job;
  job.sampleHandler (sh); // use SampleHandler in this job
  job.options()->setDouble (EL::Job::optMaxEvents, 250); // for testing purposes, limit to run over the first 500 events only!

  // add our algorithm to the job
  MyAlgorithm *alg = new MyAlgorithm;
  //alg->electronDef = "default";
  alg->muonDef = "default";
  // alg->tauDef = "default";
  // alg->photonDef = "default";
  // alg->jetDef = "default";
  // alg->metDef = "default";
  // alg->orDef = "default";
  
  
  // later on we'll add some configuration options for our algorithm that go here

  job.algsAdd (alg);

  // make the driver we want to use:
  // this one works by running the algorithm directly:
  EL::DirectDriver driver;
  // we can use other drivers to run things on the Grid, with PROOF, etc.

  // process the job using the driver
  driver.submit (job, submitDir);
}
