import cppyy
import os
import sys
from pathlib import Path

class FaustModule:
    def __init__(self):
        # Add the path to your DspFaust files
        current_dir = Path(__file__).parent
        self._setup_cppyy()
        
    def _setup_cppyy(self):
        """Set up cppyy with the DspFaust headers and implementation"""
        try:
            # Include necessary C++ headers
            cppyy.include('iostream')
            cppyy.include('cstdint')
            cppyy.include('vector')
            cppyy.include('string')
            
            # Load the DspFaust header
            cppyy.include('DspFaust.h')
            
            # Define the DspFaust class in Python
            self._define_faust_class()
            
        except Exception as e:
            print(f"Error setting up cppyy: {e}")
            raise
    
    def _define_faust_class(self):
        """Define the Python wrapper for DspFaust"""
        
        # Get the C++ DspFaust class
        self.DspFaust = cppyy.gbl.DspFaust
        
    def create_faust_instance(self, sample_rate=44100, buffer_size=512):
        """
        Create a DspFaust instance
        
        Args:
            sample_rate (int): Audio sample rate
            buffer_size (int): Audio buffer size
            
        Returns:
            DspFaust instance
        """
        try:
            # Create instance using smart pointer or direct construction
            # Based on the header, it likely uses direct construction
            faust_instance = self.DspFaust(sample_rate,, buffer_size)
            return faust_instance
        except Exception as e:
            print(f"Error creating Faust instance: {e}")
            raise

# Convenience functions
def create_faust(sample_rate=44100, buffer_size=512):
    """Create and return a DspFaust instance"""
    module = FaustModule()
    return module.create_faust_instance(sample_rate, buffer_size)

# Example usage class
class FaustProcessor:
    def __init__(self, sample_rate=44100, buffer_size=512):
        self.faust_module = FaustModule()
        self.faust = self.faust_module.create_faust_instance(sample_rate, buffer_size)
        self.sample_rate = sample_rate
        self.buffer_size = buffer_size
        
    def start(self):
        """Start the Faust engine"""
        if hasattr(self.faust, 'start'):
            return self.faust.start()
        return False
    
    def stop(self):
        """Stop the Faust engine"""
        if hasattr(self.faust, 'stop'):
            return self.faust.stop()
        return False
    
    def set_parameter_value(self, param_id, value):
        """Set a parameter value"""
        if hasattr(self.faust, 'setParamValue'):
            # Try different possible method names
            if hasattr(self.faust, 'setParamValue'):
                return self.faust.setParamValue(param_id, value)
            elif hasattr(self.faust, 'setParameterValue'):
                return self.faust.setParameterValue(param_id, value)
        return False
    
    def get_parameter_value(self, param_id):
        """Get a parameter value"""
        if hasattr(self.faust, 'getParamValue'):
            if hasattr(self.faust, 'getParamValue'):
                return self.faust.getParamValue(param_id)
            elif hasattr(self.faust, 'getParameterValue'):
                return self.faust.getParameterValue(param_id)
        return 0.0
    
    def compute(self, input_buffer):
        """
        Process audio through Faust
        
        Args:
            input_buffer: Input audio buffer (numpy array or list)
            
        Returns:
            Processed audio buffer
        """
        try:
            # Convert input to C++ vector if needed
            if hasattr(self.faust, 'compute'):
                # This will depend on the exact compute signature
                # You may need to adapt this based on the actual method
                output = self.faust.compute(len(input_buffer), input_buffer)
                return output
        except Exception as e:
            print(f"Error in compute: {e}")
            return input_buffer
    
    def get_ui(self):
        """Get UI description if available"""
        if hasattr(self.faust, 'getUI'):
            return self.faust.getUI()
        return None
    
    def get_metadata(self):
        """Get metadata if available"""
        if hasattr(self.faust, 'getMetadata'):
            return self.faust.getMetadata()
        return None

# Export main classes
__all__ = ['FaustModule', 'FaustProcessor', 'create_faust']
