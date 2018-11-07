#!/bin/bash

awk '
    BEGIN { found = 0; }
    /#/ {
        if (!found) {
            found = 1;
            $0 = substr($0, index($0, "#") + 1);
        }
    }
    /#/ {
        if (found) {
            found = 2;
            $0 = substr($0, 0, index($0, "#") - 1);
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