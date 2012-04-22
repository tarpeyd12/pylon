POGEL::TRIANGLE
POGEL::OBJECT::gettransformedtriangle(unsigned long i)
{
    // make a matrix for this objects position and rotation
    //POGEL::MATRIX mat(position,rotation);

    // if the object is facing the camera
    if( properties & OBJECT_ROTATE_TOCAMERA )
    {
        // be uesfull and do nothing
        // need to put code here
    }

    // make a transformed triangle from the triangle at the given index i
    //POGEL::TRIANGLE tri = mat.transformTriangle(face[i]);
    POGEL::TRIANGLE tri( face[ i ] );
    if( matrix.getposition() != position )
    {
        matrix = POGEL::MATRIX( position, rotation );
    }

    matrix.transformTriangle( &tri );

    // make the new triangles bounding
    tri.makebounding();

    // return the transformed triangle temporary
    return tri;
}
