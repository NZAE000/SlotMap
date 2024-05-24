# SlotMap
This work consists of how to implement a data structure called slotmap for the management of resources such as components in an engine. First, what is done before the implementation of the slotmap is to be able to see our data in memory, which first implements a utility that will allow the visualization of the data in memory through the console.

NOTA PARA IMPLEMENTAR SLOTMAP:

    Miembros de un Slotmap: { freelist, indices[ {id_, gen_},.. ], generation, data[], erase[] }

INSERTAR:
 1. Obtener la posición disponible en el arreglo de componentes(data[]) mediante 'data.size()', siendo la misma posición en el arreglo de posiciones al arreglo indices[] (erase[]).
 2. Crear variables 'id' y 'gen', tal que al 'id' se le asigna la posición hallada anteriormente y a 'gen' se le asigna el valor de generación actual. Luego se aumenta generación actual (++current_gen).
 3. Ya listo las variable 'id' y 'gen', se debe saber cual es la primera posición libre en 'indices[]' para asignar tales valores al elemento libre en tal posición libre. 
 Para ello, primero se debe actualizar el valor del miembro 'freelist': se copia el valor de 'freelist' en una variable 'pos_free', se accede al elemento libre en 'pos_free' del arreglo indices[] y se actualiza el 'freelist' con el valor del miembro 'id_' del elemento libre.
 Luego, se asigna los valores de las variable 'id' y 'gen' en los miembros 'id_' y 'gen_' del elemento libre.
 4. Se inserta el componente en el arreglo de componentes (data[]) y se inserta el valor de 'pos_free' en el arreglo de posiciones al slotmap (erase[]).
 5. Devolver un objeto 'key' al usuario (key { pos_indice ('pos_free'), gen }).

BORRAR:
 1. Para borrar un componente, el usuario debe entreagr la 'key' completa (key { pos_indice, gen } ).
 2. Acceder al objeto {id_, gen_} ubicado en 'key.pos_indice' del arreglo indices[].
 3. Verificar que key.gen == gen_ para saber que la 'key' dada es correcta, de lo contrario lanzar error(nunca debería ser incorrecta).
 4. Guardar el valor de 'id_' en una variable 'id', ya que es el valor que representa la posición donde esta el componente a eliminar.
 5. Dejar el objeto {id_, gen_} libre, entonces asignar el valor de 'freelist' al miembro 'id_' y actualizar 'freelist' con el valor de 'key.pos_indice'. 
 6. Eliminar el componente ubicado en la posición 'id' del data[] y eliminar el elemento que representa la posicón al indices[] ubicado en la posición 'id' del erase[].

 SI VARIABLE 'id' ES LA POSICIÓN DE UN COMPONENTE AL MEDIO DE 'data[]': 
  7. Mover el ultimo componente a la posicón 'id' en data[] y mover el ultimo elemento de erase[] a la poisicón 'id'.
  8. Como el componente fue movido, por ende tiene otra posicón en data[], entonces hay que actualizar su elemento correspondiente en el arreglo indices[], tal que para acceder a ese objeto {id_, gen_} es necesario la posición, la cual es el elemento movido en la posición 'id' en el arreglo erase[]. Entonces, guardar el valor erase['id'] en una variable 'pos_indice'.
  9. Acceder al objeto {id_, gen_} ubicado en 'pos_indice' y actualizar el miembro 'id_' con el valor de 'id'.
