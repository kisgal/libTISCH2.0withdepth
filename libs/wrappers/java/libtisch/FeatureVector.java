/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package libtisch;

public class FeatureVector extends FeatureBase {
  private long swigCPtr;

  protected FeatureVector(long cPtr, boolean cMemoryOwn) {
    super(libtischJNI.SWIGFeatureVectorUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(FeatureVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        libtischJNI.delete_FeatureVector(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Vector result() {
    return new Vector(libtischJNI.FeatureVector_result(swigCPtr, this), true);
  }

  public void bounds(vectorVector _bounds) {
    libtischJNI.FeatureVector_bounds(swigCPtr, this, vectorVector.getCPtr(_bounds), _bounds);
  }

  public int next() {
    return libtischJNI.FeatureVector_next(swigCPtr, this);
  }

  public void load(InputState state) {
    libtischJNI.FeatureVector_load(swigCPtr, this, InputState.getCPtr(state), state);
  }

  public String name() {
    return libtischJNI.FeatureVector_name(swigCPtr, this);
  }

  public void serialize(SWIGTYPE_p_std__ostream s) {
    libtischJNI.FeatureVector_serialize(swigCPtr, this, SWIGTYPE_p_std__ostream.getCPtr(s));
  }

  public void unserialize(SWIGTYPE_p_std__istream s) {
    libtischJNI.FeatureVector_unserialize(swigCPtr, this, SWIGTYPE_p_std__istream.getCPtr(s));
  }

  public static FeatureVector dynamic_cast(FeatureBase base) {
    long cPtr = libtischJNI.FeatureVector_dynamic_cast(FeatureBase.getCPtr(base), base);
    return (cPtr == 0) ? null : new FeatureVector(cPtr, false);
  }

}
