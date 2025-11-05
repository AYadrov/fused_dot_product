class Type:
    """Base class for numerical types."""
    def to_spec(self):
        raise NotImplementedError
        
    def __str__(self):
        raise NotImplementedError
    
    @classmethod
    def random_generator(cls):
        raise NotImplementedError

