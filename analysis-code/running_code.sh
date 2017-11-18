for f in ~/work-stuff/data/*_1e5_13tev-*.root
do
  echo "$f"
  ln -s $f ./event.root
  sleep 5
  MakeClass event.root
  hepgcc main-analysis.cc
  mpiexec -np 16 ./a.out
  mv histos_2_0.2_2_500.root ../plots/alphaSplots/$(basename "$f")
  rm event.*
done

