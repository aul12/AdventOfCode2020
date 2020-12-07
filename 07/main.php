<?php
class NumberedBag {
    public $num;
    public $color;
}

function count_inner($color, $bag_config) {
    if (array_key_exists($color, $bag_config)) {
        $inners = $bag_config[$color];
        if (count($inners) == 0) {
            return 1;
        }

        $sum = 0;
        foreach ($inners as $inner) {
            $inner_count = count_inner($inner->color, $bag_config);
            $sum += ($inner_count+1) * $inner->num; 
        }
        return $sum;
    } else {
        return 1;
    }
}

$handle = fopen("input", "r");
if ($handle) {
    $bag_configs = array();

    while (($line = fgets($handle)) !== false) {
        $splitted = explode(" bags contain ", $line);
        $outer = $splitted[0];
        $inners_splitted = explode(", ", $splitted[1]);
        $inners = array();
        foreach ($inners_splitted as $inner) {
            $words = explode(" ", $inner);
            $numBag = new NumberedBag();
            $numBag->num = intval($words[0]);
            $numBag->color = $words[1]." ".$words[2];
            array_push($inners, $numBag);
        }

        $bag_configs[$outer] = $inners;
    }
    fclose($handle);
    
    $valid_outer_bags = array();
    $changed = false;
    $count = 0;
    do {
        foreach ($bag_configs as $outer => $inners) {
            foreach ($inners as $inner) {
                if ($inner->color == "shiny gold" && $inner->num > 0 && !array_key_exists($outer, $valid_outer_bags)) {
                    $valid_outer_bags[$outer] = true;
                    $changed = true;
                } else {
                    foreach ($valid_outer_bags as $valid_outer_bag => $mll) {
                        if ($valid_outer_bag == $inner->color && $inner->num > 0 && !array_key_exists($outer, $valid_outer_bags)) {
                            $valid_outer_bags[$outer] = true;
                            $changed = true;
                        }
                    }
                }
            }
        } 
    } while ($changed && ++$count < 100);
    echo count($valid_outer_bags)."\n";

    echo count_inner("shiny gold", $bag_configs)."\n";

} else {
    printf("Error opening file");
} 
?>
