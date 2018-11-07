#!/bin/bash

awk '
    BEGIN { found = 0; }
    /_/ {
        if (!found) {
            found = 1;
            $0 = substr($0, index($0, "_") + 1);
        }
    }
    /_/ {
        if (found) {
            found = 2;
            $0 = substr($0, 0, index($0, "_") - 1);
        }
    }   
        { if (found) {
            print;
            if (found == 2) {
                found = 0;
            }
        }
    }
'