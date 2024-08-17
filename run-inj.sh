#!/bin/bash

DIR=`dirname -- $0`
FQDIR=`realpath -- $DIR`

machines=(anchovy barracuda blowfish bonito brill bullhead char cod dorado eel flounder grouper halibut herring mackerel marlin perch pollock sardine shark sole swordfish tarpon turbot tuna wahoo)

rm -f $DIR/inj-scripts/inj-*.sh
mkdir -p $DIR/inj-scripts

for m in ${machines[@]}
do
cat > $DIR/inj-scripts/inj-$m.sh <<-EOF
#!/bin/bash

function clean_exit() {
  echo "stopping..."
  exit 1
}
trap 'clean_exit' SIGINT

EOF
done

echo "creating scripts..."

i=0
for dim in 1 2 3
do
  for d in $DIR/${dim}d/*/*;
  do
    m=${machines[$((i%26))]}
  
    HL=`echo $d | sed "s~$DIR/.d/~~"`  
    H=`echo $HL | cut -d'/' -f1`
    L=`echo $HL | cut -d'/' -f2`
  
    T=`echo $((3*H>10 ? 3*H : 10))`
    N=`echo $((3*L>50 ? 3*L : 50))`
  
    echo "echo NUM_RUNS=500 $DIR/${dim}d/$H/$L/bin/star*d1r.$H.$L.*inj $T $N" >> $DIR/inj-scripts/inj-$m.sh
    echo "NUM_RUNS=500 $DIR/log.sh $DIR/${dim}d/$H/$L/bin/star*d1r.$H.$L.*inj $T $N" >> $DIR/inj-scripts/inj-$m.sh
    echo "" >> $DIR/inj-scripts/inj-$m.sh
    
  
    i=$((i+1))
  done
done

chmod +x $DIR/inj-scripts/inj-*.sh

echo "launching..."

for m in ${machines[@]}
do
  echo "ssh $m \"tmux new-session -d -s abft-inj 'exec $FQDIR/inj-scripts/inj-$m.sh'\""
  ssh $m "tmux new-session -d -s abft-inj 'exec $FQDIR/inj-scripts/inj-$m.sh'"
done
