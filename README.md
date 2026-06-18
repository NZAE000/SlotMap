# Slotmap structure
This work consists of how to implement a data structure called 'slotmap' for the management of resources such as components (data) in an engine. First, what is done before the implementation of the slotmap is to be able to see our data in memory, which first implements a utility named 'memviewer' that will allow the visualization of the data in memory through the console.
Slotmap autor: Allan Deutsch. See video: https://www.youtube.com/watch?v=SHaAR7XPtNU.

# HOW TO RUN
## Compile: make -j
## Execute: ./exec
## Clean: make clean

# DOCUMENTATION: HOW THE SLOTMAP IS IMPLEMENTED

    Slotmap members: { freelist, indices[ {id_, gen_}, ... ], generation, data[], erase[], size, capacity }

## INSERT:
 1. The user provides the element to be inserted.
 2. A free slot key must be used: obtain the position of the first available slot key (key_index) from the value of 'freelist'.
 3. Then, 'freelist' must be updated: retrieve the free slot key ('indices[key_index]') and assign the free slot key's 'id_' value to 'freelist'. Do not forget to update 'size' and 'generation'.
 4. Insert the element into 'data' at the next available position ('size - 1'), store 'key_index' in 'erase' at the available position to keep track of the slot key associated with the element, and return the key to the user ({key_index, gen}).

## ERASE:
 1. To remove an element, the user must provide the complete key ({ key_index, gen }).
 2. Verify that the key is valid ('key_index < capacity' and 'gen == indices[key_index].gen_'); otherwise, give an error (this should never happen unless there is an implementation bug).
 3. Free the slot key and update 'freelist': obtain the slot key using position 'key_index' in 'indices', store the slot key's 'id_' value in a variable (index_data), since it corresponds to the position of the element to be removed. Assign the value of 'freelist' to the slot key's 'id_' member and update 'freelist' to 'key_index'.
 6. Remove the element: if index_data is the last position, do nothing. Otherwise, copy the last element of 'data' into position index_data, and do the same for the last element of 'erase'. Then, access the slot key using the position stored in erase ('erase[index_data]') and update its 'id_' value to the new position (index_data) associated with the moved element.