/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class vectorInt : IDisposable, System.Collections.IEnumerable
#if !SWIG_DOTNET_1
    , System.Collections.Generic.IList<int>
#endif
 {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal vectorInt(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(vectorInt obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~vectorInt() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libtischPINVOKE.delete_vectorInt(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public vectorInt(System.Collections.ICollection c) : this() {
    if (c == null)
      throw new ArgumentNullException("c");
    foreach (int element in c) {
      this.Add(element);
    }
  }

  public bool IsFixedSize {
    get {
      return false;
    }
  }

  public bool IsReadOnly {
    get {
      return false;
    }
  }

  public int this[int index]  {
    get {
      return getitem(index);
    }
    set {
      setitem(index, value);
    }
  }

  public int Capacity {
    get {
      return (int)capacity();
    }
    set {
      if (value < size())
        throw new ArgumentOutOfRangeException("Capacity");
      reserve((uint)value);
    }
  }

  public int Count {
    get {
      return (int)size();
    }
  }

  public bool IsSynchronized {
    get {
      return false;
    }
  }

#if SWIG_DOTNET_1
  public void CopyTo(System.Array array)
#else
  public void CopyTo(int[] array)
#endif
  {
    CopyTo(0, array, 0, this.Count);
  }

#if SWIG_DOTNET_1
  public void CopyTo(System.Array array, int arrayIndex)
#else
  public void CopyTo(int[] array, int arrayIndex)
#endif
  {
    CopyTo(0, array, arrayIndex, this.Count);
  }

#if SWIG_DOTNET_1
  public void CopyTo(int index, System.Array array, int arrayIndex, int count)
#else
  public void CopyTo(int index, int[] array, int arrayIndex, int count)
#endif
  {
    if (array == null)
      throw new ArgumentNullException("array");
    if (index < 0)
      throw new ArgumentOutOfRangeException("index", "Value is less than zero");
    if (arrayIndex < 0)
      throw new ArgumentOutOfRangeException("arrayIndex", "Value is less than zero");
    if (count < 0)
      throw new ArgumentOutOfRangeException("count", "Value is less than zero");
    if (array.Rank > 1)
      throw new ArgumentException("Multi dimensional array.", "array");
    if (index+count > this.Count || arrayIndex+count > array.Length)
      throw new ArgumentException("Number of elements to copy is too large.");
    for (int i=0; i<count; i++)
      array.SetValue(getitemcopy(index+i), arrayIndex+i);
  }

#if !SWIG_DOTNET_1
  System.Collections.Generic.IEnumerator<int> System.Collections.Generic.IEnumerable<int>.GetEnumerator() {
    return new vectorIntEnumerator(this);
  }
#endif

  System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() {
    return new vectorIntEnumerator(this);
  }

  public vectorIntEnumerator GetEnumerator() {
    return new vectorIntEnumerator(this);
  }

  // Type-safe enumerator
  /// Note that the IEnumerator documentation requires an InvalidOperationException to be thrown
  /// whenever the collection is modified. This has been done for changes in the size of the
  /// collection but not when one of the elements of the collection is modified as it is a bit
  /// tricky to detect unmanaged code that modifies the collection under our feet.
  public sealed class vectorIntEnumerator : System.Collections.IEnumerator
#if !SWIG_DOTNET_1
    , System.Collections.Generic.IEnumerator<int>
#endif
  {
    private vectorInt collectionRef;
    private int currentIndex;
    private object currentObject;
    private int currentSize;

    public vectorIntEnumerator(vectorInt collection) {
      collectionRef = collection;
      currentIndex = -1;
      currentObject = null;
      currentSize = collectionRef.Count;
    }

    // Type-safe iterator Current
    public int Current {
      get {
        if (currentIndex == -1)
          throw new InvalidOperationException("Enumeration not started.");
        if (currentIndex > currentSize - 1)
          throw new InvalidOperationException("Enumeration finished.");
        if (currentObject == null)
          throw new InvalidOperationException("Collection modified.");
        return (int)currentObject;
      }
    }

    // Type-unsafe IEnumerator.Current
    object System.Collections.IEnumerator.Current {
      get {
        return Current;
      }
    }

    public bool MoveNext() {
      int size = collectionRef.Count;
      bool moveOkay = (currentIndex+1 < size) && (size == currentSize);
      if (moveOkay) {
        currentIndex++;
        currentObject = collectionRef[currentIndex];
      } else {
        currentObject = null;
      }
      return moveOkay;
    }

    public void Reset() {
      currentIndex = -1;
      currentObject = null;
      if (collectionRef.Count != currentSize) {
        throw new InvalidOperationException("Collection modified.");
      }
    }

#if !SWIG_DOTNET_1
    public void Dispose() {
        currentIndex = -1;
        currentObject = null;
    }
#endif
  }

  public void Clear() {
    libtischPINVOKE.vectorInt_Clear(swigCPtr);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Add(int x) {
    libtischPINVOKE.vectorInt_Add(swigCPtr, x);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  private uint size() {
    uint ret = libtischPINVOKE.vectorInt_size(swigCPtr);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private uint capacity() {
    uint ret = libtischPINVOKE.vectorInt_capacity(swigCPtr);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void reserve(uint n) {
    libtischPINVOKE.vectorInt_reserve(swigCPtr, n);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public vectorInt() : this(libtischPINVOKE.new_vectorInt__SWIG_0(), true) {
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public vectorInt(vectorInt other) : this(libtischPINVOKE.new_vectorInt__SWIG_1(vectorInt.getCPtr(other)), true) {
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public vectorInt(int capacity) : this(libtischPINVOKE.new_vectorInt__SWIG_2(capacity), true) {
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  private int getitemcopy(int index) {
    int ret = libtischPINVOKE.vectorInt_getitemcopy(swigCPtr, index);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private int getitem(int index) {
    int ret = libtischPINVOKE.vectorInt_getitem(swigCPtr, index);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private void setitem(int index, int val) {
    libtischPINVOKE.vectorInt_setitem(swigCPtr, index, val);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddRange(vectorInt values) {
    libtischPINVOKE.vectorInt_AddRange(swigCPtr, vectorInt.getCPtr(values));
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public vectorInt GetRange(int index, int count) {
    IntPtr cPtr = libtischPINVOKE.vectorInt_GetRange(swigCPtr, index, count);
    vectorInt ret = (cPtr == IntPtr.Zero) ? null : new vectorInt(cPtr, true);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Insert(int index, int x) {
    libtischPINVOKE.vectorInt_Insert(swigCPtr, index, x);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void InsertRange(int index, vectorInt values) {
    libtischPINVOKE.vectorInt_InsertRange(swigCPtr, index, vectorInt.getCPtr(values));
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveAt(int index) {
    libtischPINVOKE.vectorInt_RemoveAt(swigCPtr, index);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void RemoveRange(int index, int count) {
    libtischPINVOKE.vectorInt_RemoveRange(swigCPtr, index, count);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public static vectorInt Repeat(int value, int count) {
    IntPtr cPtr = libtischPINVOKE.vectorInt_Repeat(value, count);
    vectorInt ret = (cPtr == IntPtr.Zero) ? null : new vectorInt(cPtr, true);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Reverse() {
    libtischPINVOKE.vectorInt_Reverse__SWIG_0(swigCPtr);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Reverse(int index, int count) {
    libtischPINVOKE.vectorInt_Reverse__SWIG_1(swigCPtr, index, count);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetRange(int index, vectorInt values) {
    libtischPINVOKE.vectorInt_SetRange(swigCPtr, index, vectorInt.getCPtr(values));
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Contains(int value) {
    bool ret = libtischPINVOKE.vectorInt_Contains(swigCPtr, value);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int IndexOf(int value) {
    int ret = libtischPINVOKE.vectorInt_IndexOf(swigCPtr, value);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LastIndexOf(int value) {
    int ret = libtischPINVOKE.vectorInt_LastIndexOf(swigCPtr, value);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Remove(int value) {
    bool ret = libtischPINVOKE.vectorInt_Remove(swigCPtr, value);
    if (libtischPINVOKE.SWIGPendingException.Pending) throw libtischPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}
